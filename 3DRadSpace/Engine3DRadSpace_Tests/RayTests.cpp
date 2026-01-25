#include "pch.h"
#include <Engine3DRadSpace\Math\Ray.hpp>
#include <Engine3DRadSpace\Math\Triangle.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;

TEST(IntersectionTests, Ray_Triangle1)
{
	Ray r(Vector3(0, 0, 0), Vector3(0, 0, 1));

	Triangle tri
	{
		Vector3(-1, -1, 10),
		Vector3(1, -1, 10),
		Vector3(0, 1, 10),
	};

	EXPECT_FLOAT_EQ(r.Intersects(tri), 10.0f);
}

TEST(IntersectionTests, Ray_Triangle2)
{
	//Ray is in opposite direction
	Ray r(Vector3(0, 0, 0), Vector3(0, 0, -1));

	Triangle tri
	{
		Vector3(-1, -1, 10),
		Vector3(1, -1, 10),
		Vector3(0, 1, 10),
	};

	EXPECT_TRUE(std::isnan(r.Intersects(tri)));
}

TEST(IntersectionTests, Ray_Triangle3)
{
	//Ray is parallel to the triangle
	Ray r(
		Vector3(0, 0, 0),
		Vector3(0,0,1)
	);

	Triangle tri
	{
		Vector3(-1,2,-1),
		Vector3(-1,2,1),
		Vector3(0,2,5),
	};

	EXPECT_TRUE(std::isnan(r.Intersects(tri)));
}

TEST(IntersectionTests, Ray_Sphere1)
{
	Ray r(
		Vector3::Zero(),
		Vector3::UnitZ()
	);

	BoundingSphere sph(
		Vector3(0.1, 0, 5),
		0.125f
	);

	EXPECT_FALSE(std::isnan(r.Intersects(sph)));
}

TEST(IntersectionTests, Ray_Sphere2)
{
	Ray r(
		Vector3::Zero(),
		Vector3::UnitZ()
	);

	BoundingSphere sph(
		Vector3::One(),
		0.5f
	);

	EXPECT_TRUE(std::isnan(r.Intersects(sph)));
}