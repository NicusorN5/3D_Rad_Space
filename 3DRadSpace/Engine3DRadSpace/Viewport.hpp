/// ------------------------------------------------------------------------------------------------
/// File:   Viewport.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once

#include "Math/Rectangle.hpp"
#include "Math/Matrix4x4.hpp"

namespace Engine3DRadSpace
{
	struct Viewport
	{
		Viewport(Math::RectangleF r, float mind, float maxd) : ScreenRectangle(r), MinDepth(mind), MaxDepth(maxd) {};

		Math::RectangleF ScreenRectangle;

		float MinDepth;
		float MaxDepth;

		Math::Vector3 Unproject(const Math::Vector3& source, const Math::Matrix4x4& projection, const Math::Matrix4x4& view, const Math::Matrix4x4& world) const;
	};
}

