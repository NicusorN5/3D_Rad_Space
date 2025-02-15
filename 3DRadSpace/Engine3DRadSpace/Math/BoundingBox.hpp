/// ------------------------------------------------------------------------------------------------
/// File:   Math/BoundingBox.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct BoundingSphere;
	struct Plane;
	struct Ray;
	struct DLLEXPORT BoundingBox
	{
		Vector3 Position;
		Vector3 Scale;

		BoundingBox() = default;
		BoundingBox(const Vector3& pos, const Vector3& scale);
		BoundingBox(const BoundingSphere& sphere);
		BoundingBox(const BoundingBox& box1, const BoundingBox& box2);
		BoundingBox(const BoundingBox& box, const BoundingSphere& sphere);
		BoundingBox(const BoundingSphere& sph1,const BoundingSphere& sph2);

		Vector3 Min() const noexcept;
		Vector3 Center() const noexcept;
		Vector3 Max() const noexcept;

		bool Intersects(const BoundingBox& box) const noexcept;
		bool Intersects(const BoundingSphere& sphere) const noexcept;
		bool Intersects(const Plane& plane) const noexcept;
		bool Intersects(const Ray& ray) const noexcept;

		bool Contains(const Vector3& p) const noexcept;

		Vector3 operator[](int i) const;
	};
}