/// ------------------------------------------------------------------------------------------------
/// File:   Audio/Sound.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "Sound.hpp"
#include "../Internal/AssetUUIDReader.hpp"
#include "../Logging/Exception.hpp"
#include <al.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Reflection;

AudioBuffer Sound::_attemptLoading(const std::filesystem::path& path)
{
	auto wav = AudioBuffer::FromWAV(path);
	if(wav.has_value()) return std::move(wav.value());

	throw Exception("Failed to load a sound file! Invalid format or corrupted file!");
}

Sound::Sound(Internal::AssetUUIDReader dummy) :
	_audio(nullptr),
	_sound(nullptr,0,0,0,0,0),
	_bufferID(0)
{
}

Sound::Sound(AudioEngine *audio, const std::filesystem::path& path) :
	_audio(audio),
	_sound(std::move(_attemptLoading(path)))
{
	//Generate OpenAL sound buffer
    alGenBuffers(1, &_bufferID); //Create one buffer
	alBufferData(_bufferID, _sound._format, _sound._buffer.get(), _sound._size, _sound._sampleRate); //Set buffer.
}

Reflection::UUID Sound::GetUUID() const noexcept
{
	// {D975E8DE-7373-4560-90FB-9C19B846FCD6}
	return { 0xd975e8de, 0x7373, 0x4560, { 0x90, 0xfb, 0x9c, 0x19, 0xb8, 0x46, 0xfc, 0xd6 } };
}

const char* Sound::FileExtension() const noexcept
{
	return "Waveform Audio File Format(*.wav)\0 *.x\0"
			"All Files(*.*)\0*.*\0\0";
}

Sound::~Sound()
{
	alDeleteBuffers( 1, &_bufferID);
}