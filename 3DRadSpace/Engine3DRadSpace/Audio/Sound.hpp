/// ------------------------------------------------------------------------------------------------
/// File:   Audio/Sound.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "../Content/IAsset.hpp"
#include "AudioEngine.hpp"
#include "AudioBuffer.hpp"

namespace Engine3DRadSpace::Audio
{
	class SoundInstance;
	/// <summary>
	/// Represents a audio clip.
	/// </summary>
	class Sound : public Content::IAsset
	{
	protected:
		AudioEngine* _audio;
		AudioBuffer _sound;
		unsigned int _bufferID;
	
		AudioBuffer _attemptLoading(const std::filesystem::path& path);
	public:
		Sound(AudioEngine* audio, const std::filesystem::path& path);

		Sound(const Sound&) = delete;
		Sound(Sound&&) = default;

		Sound& operator=(const Sound&) = delete;
		Sound& operator=(Sound&&) = default;

		// Inherited via IAsset
		Reflection::UUID GetUUID() const noexcept override;
		const char* FileExtension() const noexcept override;

		~Sound();

		friend class SoundInstance;
	};
}