/// ------------------------------------------------------------------------------------------------
/// File:   Math/BoundingBoundingPlane.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "BoundingPlane.hpp"
#include "BoundingBox.hpp"
#include "BoundingSphere.hpp"
#include "Ray.hpp"

using namespace Engine3DRadSpace::Math;

bool BoundingPlane::Intersects(const BoundingBox& box) const
{
    return box.Intersects(*this);
}

bool BoundingPlane::Intersects(const BoundingSphere& sphere) const
{
    return sphere.Intersects(*this);
}

bool BoundingPlane::Intersects(const Ray& ray) const 
{
    return ray.Intersects(*this).has_value();
}

bool Engine3DRadSpace::Math::BoundingPlane::Contains(const Vector3& p) const
{
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    //The point is contained inside the plane, if the coordinates satisfy the plane equation N_x * x + N_y * y + N_z * z == D
    float p_eval = Normal.X * p.X + Normal.Y * p.Y + Normal.Z * p.Z;

    return (D - epsilon) <= p_eval && p_eval <= (D + epsilon);
}
