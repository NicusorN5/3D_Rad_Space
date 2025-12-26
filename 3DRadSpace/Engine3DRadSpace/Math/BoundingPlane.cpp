#include "BoundingPlane.hpp"
#include "BoundingPlane.h"
#include "BoundingBox.hpp"
#include "BoundingBox.h"
#include "BoundingSphere.hpp"
#include "BoundingSphere.h"
#include "Ray.hpp"
#include "Ray.h"

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

_Bool E3DRSP_BoundingPlane_IntersectsBox(E3DRSP_BoundingPlane* plane, const E3DRSP_BoundingBox* box)
{
	return reinterpret_cast<BoundingPlane*>(plane)->Intersects(*reinterpret_cast<const BoundingBox*>(box));
}

_Bool E3DRSP_BoundingPlane_IntersectsSphere(E3DRSP_BoundingPlane* plane, const E3DRSP_BoundingSphere* sphere)
{
	return reinterpret_cast<BoundingPlane*>(plane)->Intersects(*reinterpret_cast<const BoundingSphere*>(sphere));
}

_Bool E3DRSP_BoundingPlane_IntersectsRay(E3DRSP_BoundingPlane* plane, const E3DRSP_Ray* ray)
{
	return reinterpret_cast<BoundingPlane*>(plane)->Intersects(*reinterpret_cast<const Ray*>(ray));
}

_Bool E3DRSP_BoundingPlane_ContainsPoint(E3DRSP_BoundingPlane* plane, const E3DRSP_Vector3* p)
{
	return reinterpret_cast<BoundingPlane*>(plane)->Contains(*reinterpret_cast<const Vector3*>(p));
}