/// ------------------------------------------------------------------------------------------------
/// File:   Audio/AudioBuffer.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "AudioBuffer.hpp"
#include "../Memory.hpp"
#include <al.h>

using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Memory;

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
        if(!IsBigEndian())
            for(int i = 0; i < len; i++)
                ((char*)&a)[i] = buffer[i];
        else
            for(int i = 0; i < len; i++)
                ((char*)&a)[3 - i] = buffer[i];
        return a;
    };

    char buffer[4];

    auto fn = path.string();
    std::ifstream in(fn, std::ios::binary);
    in.read(buffer, 4);
    if(strncmp(buffer, "RIFF", 4) != 0)
    {
        return std::nullopt;
    }
    in.read(buffer, 4);
    in.read(buffer, 4);      //WAVE
    in.read(buffer, 4);      //fmt
    in.read(buffer, 4);      //16
    in.read(buffer, 2);      //1
    in.read(buffer, 2);
    int chan = convertToInt(buffer, 2);
    in.read(buffer, 4);
    int sampleRate = convertToInt(buffer, 4);
    in.read(buffer, 4);
    in.read(buffer, 2);
    in.read(buffer, 2);
    int bps = convertToInt(buffer, 2);
    in.read(buffer, 4);      //data
    in.read(buffer, 4);
    int size = convertToInt(buffer, 4);
    char* data = new char[size];
    in.read(data, size);
    
    int format;
    if (chan == 1)
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

    return AudioBuffer(data, chan, sampleRate, bps, format, size);
}