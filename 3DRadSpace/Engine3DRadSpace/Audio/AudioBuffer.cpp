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

std::expected<AudioBuffer, AudioBuffer::WAVLoadError> AudioBuffer::FromWAV(const std::filesystem::path& path)
{
	//https://stackoverflow.com/questions/36949957/loading-a-wav-file-for-openal

	// Converts a buffer to a little endian integer with size len.
	auto buffLE_toInt = [](char* buffer, int len) -> int
		{
			int a = 0;
			if (!(std::endian::native == std::endian::big))
				for (int i = 0; i < len; i++)
					((char*)&a)[i] = buffer[i];
			else
				for (int i = 0; i < len; i++)
					((char*)&a)[3 - i] = buffer[i];
			return a;
		};

	int channels;
	int sampleRate;
	int bps;
	int size;
	char buffer[4];

	std::ifstream in(path, std::ios::binary);

	if (in.bad() || in.fail())
	{
		return std::unexpected(AudioBuffer::WAVLoadError::CannotOpen);
	}

	in.read(buffer, 4);

	if (strncmp(buffer, "RIFF", 4) != 0)
	{
		//RIFF not found in header
		return std::unexpected(AudioBuffer::WAVLoadError::RIFFNotFound);
	}

	in.read(buffer, 4);//size of file. Not used. Read it to skip over it.  
	in.read(buffer, 4);//Format, should be WAVE
	if (strncmp(buffer, "WAVE", 4) != 0)
	{
		//not a valid WAV file, RIFF not found in header
		return std::unexpected(AudioBuffer::WAVLoadError::RIFFNotFound);
	}

	in.read(buffer, 4);//Format Space Marker. should equal fmt (space)

	if (strncmp(buffer, "fmt ", 4) != 0)
	{
		//not a valid WAV file, Format Marker not found in header
		return std::unexpected(AudioBuffer::WAVLoadError::NoFormatMarker);
	}

	in.read(buffer, 4);//Length of format data. Should be 16 for PCM, meaning uncompressed.

	if (buffLE_toInt(buffer, 4) != 16)
	{
		// not a valid WAV file, format length wrong in header
		return std::unexpected(AudioBuffer::WAVLoadError::WrongFormatLength);
	}

	in.read(buffer, 2);//Type of format, 1 = PCM

	if (buffLE_toInt(buffer, 2) != 1)
	{
		// not a valid WAV file, file not in PCM format
		return std::unexpected(AudioBuffer::WAVLoadError::NotPCM);
	}

	in.read(buffer, 2);//Get number of channels. 

	//Assume at this point that we are dealing with a WAV file. This value is needed by OpenAL
	channels = buffLE_toInt(buffer, 2);

	in.read(buffer, 4);//Get sampler rate. 

	sampleRate = buffLE_toInt(buffer, 4);

	//Skip Byte Rate and Block Align. Maybe use later?
	in.read(buffer, 4);//Block Align
	in.read(buffer, 2);//ByteRate

	in.read(buffer, 2);//Get Bits Per Sample

	bps = buffLE_toInt(buffer, 2);

	//Skip character data, which marks the start of the data that we care about. 
	in.read(buffer, 4); //expect "data" chunk. 

	//finds "data" chunk.
	auto ignore_chunks = [&in, &buffer, buffLE_toInt]() -> bool
	{
		auto ignore = [&in, &buffer, buffLE_toInt]() -> bool
		{
			in.read(buffer, 4); // chunk size
			int size = buffLE_toInt(buffer, 4);
			in.ignore(size);

			in.read(buffer, 4); //read next chunk

			return true;
		};

		//Case insesitive string compare
		auto cmpStr_ci = [](const char* left, const char* right, size_t n) -> bool
		{
			for (int i = 0; i < n && left[i] != 0 && right[i] != 0; ++i)
			{
				char l = std::tolower(left[i]);
				char r = std::tolower(right[i]);

				if (l != r) return false;
			}
			return true;
		};

		if (cmpStr_ci(buffer, "cue", 3)) return ignore();
		if (cmpStr_ci(buffer, "list", 4)) return ignore();
		if (cmpStr_ci(buffer, "info", 4)) return ignore();
		if (cmpStr_ci(buffer, "fact", 4)) return ignore();

		if (cmpStr_ci(buffer, "data", 4)) return false;

		return false;
	};
   
	while(ignore_chunks()){ }

	in.read(buffer, 4); //Get size of the data chunk

	size = buffLE_toInt(buffer, 4);

	if(size < 0)
	{
		//not a valid WAV file, size of file reports 0
		return std::unexpected(AudioBuffer::WAVLoadError::NullSize);
	}

	char* data = new char[size];
	if (data == nullptr)
	{
		return std::unexpected(AudioBuffer::WAVLoadError::OutOfMemory);
	}

	in.read(data, size);//Read audio data into buffer, return.

	in.close(); 
	
	int format;
	if (channels == 1)
	{
		format = bps == 8 ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
	}
	else 
	{
		format = bps == 8 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
	}

	return AudioBuffer(data, channels, sampleRate, bps, format, size);
}

std::expected<AudioBuffer, AudioBuffer::OGGLoadError> AudioBuffer::FromOGG(const std::filesystem::path& path)
{
	//https://gist.github.com/tilkinsc/f91d2a74cff62cc3760a7c9291290b29

	OggVorbis_File vf;
	
	FILE* file = fopen(path.string().c_str(), "rb");
	if(file == nullptr)
	{
		//Failed to open OGG file.
		return std::unexpected(AudioBuffer::OGGLoadError::CannotOpen);
	}

	if(ov_open_callbacks(file, &vf, nullptr, 0, OV_CALLBACKS_NOCLOSE) < 0)
	{
		//Not a valid OGG file.
		return std::unexpected(AudioBuffer::OGGLoadError::Invalid);
	}

	vorbis_info* info = ov_info(&vf, -1);
	if(info == nullptr)
	{
		//Failed to get OGG info
		ov_clear(&vf);
		return std::unexpected(AudioBuffer::OGGLoadError::InfoFail);
	}
	int channels = info->channels;
	int sampleRate = info->rate;
	int bps = 16; // Vorbis always uses 16 bits per sample
	int format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	long size = ov_pcm_total(&vf, -1) * channels * 2;
	
	char* buffer = new char[size];
	if(buffer == nullptr)
	{
		//Failed to allocate memory for OGG buffer
		ov_clear(&vf);
		return std::unexpected(AudioBuffer::OGGLoadError::OutOfMemory);
	}

	for(int64_t bytesRead = 0, offset = 0, sel=0; ; offset += bytesRead)
	{
		long read = ov_read(
			&vf,
			buffer + offset, 
			4096,
			std::endian::native == std::endian::big, // 1 if big-endian, 0 if little-endian
			sizeof(short),
			1, 
			reinterpret_cast<int*>(&sel)
		);
		if(!read) break;

		if(bytesRead < 0)
		{
			//Faulty OGG file.
			delete[] buffer;
			ov_clear(&vf);
			return std::unexpected(AudioBuffer::OGGLoadError::Invalid);
		}
	}
	ov_clear(&vf);
	fclose(file);
	return AudioBuffer(buffer, channels, sampleRate, bps, format, static_cast<int>(size));
}