#pragma once

namespace Engine3DRadSpace::Graphics
{
	enum class TextureAddressMode : unsigned char
	{
		Wrap = 1,
		Mirror = 2,
		Clamp = 3,
		Border = 4,
		MirrorOnce = 5
	};
}