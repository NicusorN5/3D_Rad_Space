/// ------------------------------------------------------------------------------------------------
/// File:   Audio/Sound.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "../Content/IAsset.hpp"
#include "AudioEngine.hpp"

namespace Engine3DRadSpace::Audio
{
	class Sound : public Content::IAsset
	{
	public:
		Sound(AudioEngine* audio, const std::filesystem::path& path);

		Sound(const Sound&) = delete;
		Sound(Sound&&) = default;

		Sound& operator=(const Sound&) = delete;
		Sound& operator=(Sound&&) = default;
	};
}