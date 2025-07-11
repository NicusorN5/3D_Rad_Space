#pragma once

#include "../Math/Rectangle.hpp"
#include "../Math/Matrix4x4.hpp"

namespace Engine3DRadSpace
{
	struct E3DRSP_GRAPHICS_EXPORT Viewport
	{
		Viewport(Math::RectangleF r, float mind, float maxd) : ScreenRectangle(r), MinDepth(mind), MaxDepth(maxd) {};

		Math::RectangleF ScreenRectangle;

		float MinDepth;
		float MaxDepth;

		Math::Vector3 Unproject(const Math::Vector3& source, const Math::Matrix4x4& projection, const Math::Matrix4x4& view, const Math::Matrix4x4& world) const;
	};
}

