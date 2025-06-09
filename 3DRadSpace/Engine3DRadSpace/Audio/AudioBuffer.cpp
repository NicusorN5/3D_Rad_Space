#include "AudioBuffer.hpp"
#include "AudioBuffer.hpp"
#include <al.h>
#include <vorbis\codec.h>
#include <vorbis\vorbisenc.h>
#include <vorbis\vorbisfile.h>

using namespace Engine3DRadSpace::Audio;

AudioBuffer::AudioBuffer(char* buffer, int channel, int sampleRate, int bps, int format, int size) :
	 _buffer(buffer),
	_channel(channel),
	_sampleRate(sampleRate),
	_bps(bps),
    _format(format),
	_size(size)
{
}

std::optional<AudioBuffer> AudioBuffer::FromWAV(const std::filesystem::path& path)
{
	//https://stackoverflow.com/questions/36949957/loading-a-wav-file-for-openal
    auto convertToInt = [](char* buffer, int len) -> int
    {
        int a = 0;
        if(!(std::endian::native == std::endian::big))
            for(int i = 0; i < len; i++)
                ((char*)&a)[i] = buffer[i];
        else
            for(int i = 0; i < len; i++)
                ((char*)&a)[3 - i] = buffer[i];
        return a;
    };

    int channels;
    int sampleRate;
    int bps;
    int size;
    char buffer[4];

    std::ifstream in(path);
    in.read(buffer, 4);

    if(strncmp(buffer, "RIFF", 4) != 0)
    {
        //"Error here, not a valid WAV file, RIFF not found in header\n This was found instead: "
        return std::nullopt;
    }

    in.read(buffer, 4);//size of file. Not used. Read it to skip over it.  
    in.read(buffer, 4);//Format, should be WAVE
    if(strncmp(buffer, "WAVE", 4) != 0)
    {
        //not a valid WAV file, RIFF not found in header
        return std::nullopt;
    }

    in.read(buffer, 4);//Format Space Marker. should equal fmt (space)

    if(strncmp(buffer, "fmt ", 4) != 0)
    {
        //not a valid WAV file, Format Marker not found in header
        return std::nullopt;
    }

    in.read(buffer, 4);//Length of format data. Should be 16 for PCM, meaning uncompressed.

    if(convertToInt(buffer, 4) != 16)
    {
        // not a valid WAV file, format length wrong in header
        return std::nullopt;
    }

    in.read(buffer, 2);//Type of format, 1 = PCM

    if(convertToInt(buffer, 2) != 1)
    {
        // not a valid WAV file, file not in PCM format
        return std::nullopt;
    }

    in.read(buffer, 2);//Get number of channels. 

    //Assume at this point that we are dealing with a WAV file. This value is needed by OpenAL
    channels = convertToInt(buffer, 2);

    in.read(buffer, 4);//Get sampler rate. 

    sampleRate = convertToInt(buffer, 4);

    //Skip Byte Rate and Block Align. Maybe use later?
    in.read(buffer, 4);//Block Align
    in.read(buffer, 2);//ByteRate

    in.read(buffer, 2);//Get Bits Per Sample

    bps = convertToInt(buffer, 2);

    //Skip character data, which marks the start of the data that we care about. 
    in.read(buffer, 4);//"data" chunk. 

    in.read(buffer, 4); //Get size of the data

    size = convertToInt(buffer, 4);

    if(size < 0)
    {
        //not a valid WAV file, size of file reports 0
        return std::nullopt;
    }

    char* data = new char[size];

    in.read(data, size);//Read audio data into buffer, return.

    in.close(); 
    
    int format;
    if (channels == 1)
    {
        if (bps == 8)
        {
            format = AL_FORMAT_MONO8;
        }
        else {
            format = AL_FORMAT_MONO16;
        }
    }
    else 
    {
        if (bps == 8)
        {
            format = AL_FORMAT_STEREO8;
        }
        else {
            format = AL_FORMAT_STEREO16;
        }
    }

    return AudioBuffer(data, channels, sampleRate, bps, format, size);
}

std::optional<AudioBuffer> AudioBuffer::FromOGG(const std::filesystem::path& path)
{
    OggVorbis_File vf;
	if(ov_fopen(path.string().c_str(), &vf) != 0)
    {
        //Failed to open OGG file
        return std::nullopt;
	}

    vorbis_info* info = ov_info(&vf, -1);
    if(info == nullptr)
    {
        //Failed to get OGG info
        ov_clear(&vf);
        return std::nullopt;
    }
    int channels = info->channels;
    int sampleRate = info->rate;
    int bps = 16; // Vorbis always uses 16 bits per sample
    int format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    long size = ov_pcm_total(&vf, -1) * channels * (bps / 8);
    
    char* buffer = new char[size];
    if(buffer == nullptr)
    {
        //Failed to allocate memory for OGG buffer
        ov_clear(&vf);
        return std::nullopt;
	}

	memset(buffer, 0, size); // Initialize buffer to zero

    long bytesRead = ov_read(
        &vf, 
        buffer, 
        size,
        std::endian::native == std::endian::big,
        2,
        1,
        nullptr
    );

    if(bytesRead < 0)
    {
        //Error reading OGG file
        delete[] buffer;
        ov_clear(&vf);
        return std::nullopt;
    }
    ov_clear(&vf);
	return AudioBuffer(buffer, channels, sampleRate, bps, format, static_cast<int>(bytesRead));
}