/// ------------------------------------------------------------------------------------------------
/// File:   Audio/SoundState.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once

namespace Engine3DRadSpace::Audio
{
	enum class SoundState : uint8_t
	{
		Undefined = 0,
		Stopped,
		Playing,
		Paused,
	};
}