#pragma once
#include "../Math/Rectangle.hpp"

namespace Engine3DRadSpace::Graphics
{
	struct Glyph
	{
		char Character;
		Math::Point Size;
		Math::Point Bearing;
		unsigned Advance;
	};
}