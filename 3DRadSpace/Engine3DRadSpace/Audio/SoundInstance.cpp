/// ------------------------------------------------------------------------------------------------
/// File:   Audio/SoundInstance.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "SoundInstance.hpp"
#include "Sound.hpp"
#include <al.h>

using namespace Engine3DRadSpace::Audio;

SoundInstance::SoundInstance(class Sound&& sound, const AudioSource& source) :
	Source(source),
	_audio(sound._audio)
{
	//create OpenAL source
	this->Sound = std::make_unique<class Sound>(std::move(sound));
	alGenSources(1, &_sourceID);

	//Assign buffer to source.
	alSourcei(_sourceID, AL_BUFFER, sound._bufferID);
		if(_audio->CheckErrors().has_value()) throw int(5);
}

SoundState Engine3DRadSpace::Audio::SoundInstance::GetState()
{
	int sourceState;
	alGetSourcei(_sourceID, AL_SOURCE_STATE, &sourceState);

	if(_audio->CheckErrors().has_value()) return SoundState::Undefined;

	switch(sourceState)
	{
		case AL_PLAYING:
			return SoundState::Playing;
		default:
			return SoundState::Undefined;
	}
}

void SoundInstance::Play()
{
	alSourcePlay(_sourceID);
		if(_audio->CheckErrors().has_value()) throw int(5);
}

SoundInstance::~SoundInstance()
{
	alDeleteSources( 1, &_sourceID);
}
