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

		/// <summary>
		/// Checks if this ray intersects with the given bounding sphere.
		/// </summary>
		/// <param name="sph">Bounding sphere.</param>
		/// <returns>Closest intersection point.</returns>
		/// <remarks>
		/// this.Direction but must be normalized.
		/// </remarks>
		float Intersects(const BoundingSphere &sph) const;
		float Intersects(const Triangle &tri) const;
		float Intersects(const BoundingBox &box) const;
		float Intersects(const BoundingPlane& plane) const;
	};
}