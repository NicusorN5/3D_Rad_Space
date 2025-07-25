#pragma once
#include "BoundingSphere.hpp"
#include "Triangle.hpp"
#include "BoundingBox.hpp"
#include "BoundingPlane.hpp"

namespace Engine3DRadSpace::Math
{
	struct E3DRSP_MATH_EXPORT Ray
	{
		Vector3 Origin;
		Vector3 Direction;

		std::optional<float> Intersects(const BoundingSphere &sph) const;
		std::optional<float> Intersects(const Triangle &tri) const;
		std::optional<float> Intersects(const BoundingBox &box) const;
		std::optional<float> Intersects(const BoundingPlane& plane) const;
	};
}