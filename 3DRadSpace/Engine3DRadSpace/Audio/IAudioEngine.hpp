#pragma once
#include "../Core/IService.hpp"
#include "AudioError.hpp"

namespace Engine3DRadSpace::Audio
{
	/// <summary>
	/// Instances and handles audio device handles.
	/// </summary>
	class IAudioEngine : public IService
	{
	public:
		virtual void SwitchAudioDevice(const std::string& deviceName) = 0;
		virtual void Update() noexcept = 0;
		virtual std::optional<AudioError> CheckErrors() = 0;

		~IAudioEngine() override = default;
	};
}