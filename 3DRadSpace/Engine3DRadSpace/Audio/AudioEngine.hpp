#pragma once
#include "AudioError.hpp"
#include "../Core/Libs.hpp"
#include "Listener.hpp"

namespace Engine3DRadSpace::Audio
{
	class SoundInstance;
	/// <summary>
	/// Instances and handles audio device handles.
	/// </summary>
	class E3DRSP_AUDIO_EXPORT AudioEngine 
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

		class Listener Listener;

		static std::vector<std::string> ListAudioDevices();

		void SwitchAudioDevice(const std::string& deviceName);

		bool HasEAX2Support() const noexcept;

		~AudioEngine();

		void Update() const noexcept;

		std::optional<AudioError> CheckErrors();
	};
}