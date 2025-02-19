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