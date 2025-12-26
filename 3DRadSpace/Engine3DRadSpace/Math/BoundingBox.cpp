#include "BoundingBox.hpp"
#include "BoundingBox.h"
#include "BoundingSphere.hpp"
#include "BoundingSphere.h"
#include "Math.hpp"
#include "Ray.hpp"
#include "Ray.h"
#include "Vector3.h"

using namespace Engine3DRadSpace::Math;

BoundingBox::BoundingBox(const Vector3& pos, const Vector3& scale):
	Position(pos),
	Scale(scale)
{
}

BoundingBox::BoundingBox(const BoundingSphere& sphere):
	Position( sphere.Center - (Vector3::One() * sphere.Radius)),
	Scale( sphere.Radius, sphere.Radius, sphere.Radius)
{
}

BoundingBox::BoundingBox(const BoundingBox& box1, const BoundingBox& box2)
{
	Vector3 minVec = Vector3(
		std::min(box1.Position.X, box2.Position.X),
		std::min(box1.Position.Y, box2.Position.Y),
		std::min(box1.Position.Z, box2.Position.Z)
	);
	Vector3 maxVec = Vector3(
		std::max(box1.Position.X, box2.Position.X),
		std::max(box1.Position.Y, box2.Position.Y),
		std::max(box1.Position.Z, box2.Position.Z)
	);
	Position = minVec;
	Scale = maxVec - minVec;
}

BoundingBox::BoundingBox(const BoundingBox& box, const BoundingSphere& sphere) : BoundingBox(BoundingSphere(sphere,box))
{
}

BoundingBox::BoundingBox(const BoundingSphere& sph1,const BoundingSphere& sph2) : BoundingBox(BoundingSphere(sph1, sph2))
{
}

Vector3 BoundingBox::Min() const noexcept
{
	return Position;
}

Vector3 BoundingBox::Max() const noexcept
{
	return Position + Scale;
}

bool BoundingBox::Intersects(const BoundingBox& box) const noexcept
{
	return  AABB(Position.X, Scale.X, box.Position.X, box.Scale.X) &&
			AABB(Position.Y, Scale.Y, box.Position.Y, box.Scale.Y) &&
			AABB(Position.Z, Scale.Z, box.Position.Z, box.Scale.Z);
}

bool BoundingBox::Intersects(const BoundingSphere& sphere) const noexcept
{
	auto ClosestPoint = [](const BoundingBox& box, const Vector3 & p) -> Vector3
	{
		float dst = std::numeric_limits<float>::max();

		for (int i = 0; i < 8; i++)
		{
			float d = (box[i] - p).LengthSquared();
			if (d < dst)
				dst = d;
		}

		return dst;
	};

	//https://gdbooks.gitbooks.io/3dcollisions/content/Chapter2/static_sphere_aabb.html
	Vector3 closestPoint = ClosestPoint(*this, sphere.Center);
	Vector3 differenceVec = sphere.Center - closestPoint;

	float distanceSquared = differenceVec.LengthSquared();
	float radiusSquared = sphere.Radius * sphere.Radius;

	return distanceSquared < radiusSquared;
}

bool BoundingBox::Intersects(const BoundingPlane& plane) const noexcept
{
	//https://gdbooks.gitbooks.io/3dcollisions/content/Chapter2/static_aabb_plane.html

	// Convert AABB to center-extents representation
	Vector3 c = Center();
	Vector3 e = Max() - c; // Compute positive extents

	// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
	float r = e.X * abs(plane.Normal.X) + e.Y * abs(plane.Normal.Y) + e.Z * abs(plane.Normal.Z);

	// Compute distance of box center from plane
	float s = Vector3::Dot(plane.Normal, c) - plane.D;

	// Intersection occurs when distance s falls within [-r,+r] interval
	return abs(s) <= r; 
}

bool BoundingBox::Intersects(const Ray& ray) const noexcept
{
	return ray.Intersects(*this).has_value();
}

bool BoundingBox::Contains(const Vector3& p) const noexcept
{
	return	Min().X >= p.X && p.X <= Max().X &&
			Min().Y >= p.Y && p.Y <= Max().Y;
}

Vector3 BoundingBox::operator[](int i) const
{
	switch (i)
	{
	case 0: return Min();
	case 1: return Position + Vector3(Scale.X, 0, 0);
	case 2: return Position + Vector3(0, Scale.Y, 0);
	case 3: return Position + Vector3(0, 0, Scale.Z);
	case 4: return Position + Vector3(Scale.X, Scale.Y, 0);
	case 5: return Position + Vector3(Scale.X, 0, Scale.Z);
	case 6: return Position + Vector3(0, Scale.Y, Scale.Z);
	case 7: return Max();
	default: throw std::out_of_range("0 <= i < 8");
	}
}

Vector3 BoundingBox::Center() const noexcept
{
	return Position + (Scale / 2);
}

E3DRSP_Vector3 E3DRSP_BoundingBox_Min(E3DRSP_BoundingBox* box)
{
	auto v = reinterpret_cast<BoundingBox*>(box)->Min();
	return { v.X, v.Y, v.Z };
}

E3DRSP_Vector3 E3DRSP_BoundingBox_Center(E3DRSP_BoundingBox* box)
{
	auto v = reinterpret_cast<BoundingBox*>(box)->Center();
	return { v.X, v.Y, v.Z };
}

E3DRSP_Vector3 E3DRSP_BoundingBox_Max(E3DRSP_BoundingBox* box)
{
	auto v = reinterpret_cast<BoundingBox*>(box)->Max();
	return { v.X, v.Y, v.Z };
}

_Bool E3DRSP_BoundingBox_IntersectsBox(E3DRSP_BoundingBox *box1, const E3DRSP_BoundingBox* box2)
{
	return reinterpret_cast<BoundingBox*>(box1)->Intersects(*std::bit_cast<const BoundingBox*>(box2));
}

_Bool E3DRSP_BoundingBox_IntersectsSphere(E3DRSP_BoundingBox *box, const E3DRSP_BoundingSphere* sphere)
{
	return reinterpret_cast<BoundingBox*>(box)->Intersects(*std::bit_cast<const BoundingSphere*>(sphere));
}

_Bool E3DRSP_BoundingBox_IntersectsPlane(E3DRSP_BoundingBox box, const E3DRSP_BoundingPlane* plane)
{
	return reinterpret_cast<BoundingBox*>(&box)->Intersects(*std::bit_cast<const BoundingPlane*>(plane));
}

_Bool E3DRSP_BoundingBox_IntersectsRay(E3DRSP_BoundingBox box, E3DRSP_Ray ray)
{
	return reinterpret_cast<BoundingBox*>(&box)->Intersects(*std::bit_cast<Ray*>(&ray));
}

_Bool E3DRSP_BoundingBox_ContainsPoint(E3DRSP_BoundingBox box, E3DRSP_Vector3 point)
{
	return reinterpret_cast<BoundingBox*>(&box)->Contains(*std::bit_cast<Vector3*>(&point));
}

E3DRSP_Vector3 E3DRSP_BoundingBox_GetCorner(E3DRSP_BoundingBox box, int index)
{
	auto v = reinterpret_cast<BoundingBox*>(&box)->operator[](index);
	return E3DRSP_Vector3{ v.X, v.Y, v.Z };
}