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

		float Intersects(const BoundingSphere &sph) const;
		float Intersects(const Triangle &tri) const;
		float Intersects(const BoundingBox &box) const;
		float Intersects(const BoundingPlane& plane) const;
	};
}