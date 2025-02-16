/// ------------------------------------------------------------------------------------------------
/// File:   Audio/AudioError.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once

namespace Engine3DRadSpace::Audio
{
	enum class AudioError : int
	{
		None = 0,
		BadID,
		InvalidEnum,
		InvalidValue,
		InvalidOperation,
		OutOfMemory,
		Unspecified = 0x7FFFFFFF,
	};
}