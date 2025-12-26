#pragma once

#include "../Math/Rectangle.hpp"
#include "../Math/Matrix4x4.hpp"

namespace Engine3DRadSpace::Graphics
{
	struct E3DRSP_GRAPHICS_EXPORT Viewport
	{
		Viewport() = default;
		Viewport(Math::RectangleF r, float mind, float maxd) : ScreenRectangle(r), MinDepth(mind), MaxDepth(maxd) {};

		Math::RectangleF ScreenRectangle;

		float MinDepth = 0.0f;
		float MaxDepth = 1.0f;

		Math::Vector3 Unproject(const Math::Vector3& source, const Math::Matrix4x4& projection, const Math::Matrix4x4& view, const Math::Matrix4x4& world) const;
	};
}