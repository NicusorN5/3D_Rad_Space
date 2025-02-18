/// ------------------------------------------------------------------------------------------------
/// File:   Math/Ray.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "BoundingSphere.hpp"
#include "Triangle.hpp"
#include "BoundingBox.hpp"
#include "BoundingPlane.hpp"

namespace Engine3DRadSpace::Math
{
	struct DLLEXPORT Ray
	{
		Vector3 Origin;
		Vector3 Direction;

		std::optional<float> Intersects(const BoundingSphere &sph) const;
		std::optional<float> Intersects(const Triangle &tri) const;
		std::optional<float> Intersects(const BoundingBox &box) const;
		std::optional<float> Intersects(const BoundingPlane& plane) const;
	};
}