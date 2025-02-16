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
	class DLLEXPORT SoundInstance
	{
		AudioEngine* _audio;
		unsigned int _sourceID;
		AudioSource _source;
		Sound* _sound;
	public:
		SoundInstance(Sound* sound, const AudioSource& source);
		SoundInstance(Sound* sound);

		const AudioSource &GetSource();
		void SetSource(const AudioSource& source);
		SoundState GetState();
		
		void SetPitch(float pitch);
		void SetGain(float gain);
		void SetMaxGain(float maxGain);
		void SetMinGain(float minGain);
		void SetPosition(const Math::Vector3& pos);
		void SetVelocity(const Math::Vector3& vel);
		void SetDirection(const Math::Vector3& dir);
		void SetMaxDistance(float distance);
		void SetReferenceDistance(float refDistance);
		void SetRolloffFactor(float rolloff);
		void SetConeOuterGain(float outerGain);
		void SetConeInnerAngle(float angle);
		void SetConeOuterAngle(float angle);

		float GetPitch();
		float GetGain();
		float GetMaxGain();
		float GetMinGain();
		Math::Vector3 GetPosition();
		Math::Vector3 GetVelocity();
		Math::Vector3 GetDirection();
		float GetMaxDistance();
		float GetReferenceDistance();
		float GetRolloffFactor();
		float GetConeOuterGain();
		float GetConeInnerAngle();
		float GetConeOuterAngle();

		bool IsLooping();
		void SetLooping(bool looping);

		void Play();
		void Stop();
		void Pause();

		~SoundInstance();
	};
}