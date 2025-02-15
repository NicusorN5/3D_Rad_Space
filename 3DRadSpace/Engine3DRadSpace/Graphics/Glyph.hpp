/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/Glyph.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
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