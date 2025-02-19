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