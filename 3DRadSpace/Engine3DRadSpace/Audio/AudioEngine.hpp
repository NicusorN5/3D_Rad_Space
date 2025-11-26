#pragma once
#include "AudioError.hpp"
#include "IAudioEngine.hpp"
#include "Listener.hpp"

namespace Engine3DRadSpace::Audio
{
	class SoundInstance;
	/// <summary>
	/// OpenAL based audio engine.
	/// </summary>
	class E3DRSP_AUDIO_EXPORT AudioEngine : public IAudioEngine
	{
		void* _audioDevice;
		void* _audioContext;

		bool _hasEAX2support = false;

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

		void SwitchAudioDevice(const std::string& deviceName) override;

		void Update() noexcept override;

		std::optional<AudioError> CheckErrors() override;

		~AudioEngine() override;
	};
}