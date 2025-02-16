/// ------------------------------------------------------------------------------------------------
/// File:   Audio/SoundInstance.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "Sound.hpp"
#include "AudioSource.hpp"
#include "SoundState.hpp"

namespace Engine3DRadSpace::Audio
{
	class SoundInstance
	{
		AudioEngine* _audio;
		unsigned int _sourceID;
	public:
		std::unique_ptr<class Sound> Sound;
		AudioSource Source;

		SoundInstance(class Sound&& sound, const AudioSource& source);

		SoundState GetState();

		void Play();

		~SoundInstance();
	};
}