/// ------------------------------------------------------------------------------------------------
/// File:   Audio/AudioEngine.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "AudioSource.hpp"
#include "../IUpdateable.hpp"

struct ALCdevice;
struct ALCcontext;
namespace Engine3DRadSpace::Audio
{
	/// <summary>
	/// Instances and handles audio device handles.
	/// </summary>
	class DLLEXPORT AudioEngine 
	{
		ALCdevice *_audioDevice;
		ALCcontext* _audioContext;

		bool _hasEAX2support = false;
	public:
		AudioEngine();

		AudioEngine(const AudioEngine&) = delete;
		AudioEngine(AudioEngine&&) = delete;

		AudioEngine& operator=(const AudioEngine&) = delete;
		AudioEngine& operator=(AudioEngine&&) = delete;

		std::vector<std::string> ListAudioDevices() const noexcept;

		void SetListener(const Math::Vector3& vector);
		void CreateAudioSource(const AudioSource& source);

		bool HasEAX2Support() const noexcept;

		~AudioEngine();

		// Inherited via IUpdateable
		void Update(double dt);
	};
}