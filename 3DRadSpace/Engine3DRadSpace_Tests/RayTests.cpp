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

	EXPECT_FLOAT_EQ(r.Intersects(tri).value(), 10.0f);
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

	EXPECT_FALSE(r.Intersects(tri).has_value());
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

	EXPECT_FALSE(r.Intersects(tri).has_value());
}