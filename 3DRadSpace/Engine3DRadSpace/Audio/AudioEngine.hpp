/// ------------------------------------------------------------------------------------------------
/// File:   Audio/AudioEngine.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "AudioError.hpp"
#include "../IUpdateable.hpp"
#include "../Math/Vector3.hpp"

namespace Engine3DRadSpace::Audio
{
	class SoundInstance;
	/// <summary>
	/// Instances and handles audio device handles.
	/// </summary>
	class DLLEXPORT AudioEngine 
	{
		void* _audioDevice;
		void* _audioContext;

		bool _hasEAX2support = false;

		std::vector<SoundInstance*> _instances;

		void _initializeContext();
	public:
		AudioEngine();
		AudioEngine(const std::string& deviceName);

		AudioEngine(const AudioEngine&) = delete;
		AudioEngine(AudioEngine&&) = delete;

		AudioEngine& operator=(const AudioEngine&) = delete;
		AudioEngine& operator=(AudioEngine&&) = delete;

		static std::vector<std::string> ListAudioDevices();

		void SetListener(const Math::Vector3& vector);

		bool HasEAX2Support() const noexcept;

		~AudioEngine();

		// Inherited via IUpdateable
		void Update(double dt);

		std::optional<AudioError> CheckErrors();
	};
}