#include "pch.h"
#include <Engine3DRadSpace/Math/Vector3.hpp>

using namespace Engine3DRadSpace::Math;

TEST(LinearAlgebraTests,Vector3_Cross1)
{
	//Basic cross product test:
	Vector3 a = Vector3::UnitX(), b = Vector3::UnitY();

	EXPECT_FLOAT_EQ(Vector3::Cross(a, b).X, 0);
	EXPECT_FLOAT_EQ(Vector3::Cross(a, b).Y, 0);
	EXPECT_FLOAT_EQ(Vector3::Cross(a, b).Z, 1);
}

TEST(LinearAlgebraTests,Vector3_Cross2)
{
	//https://mathinsight.org/cross_product_examples
	Vector3 a(3, -3, 1), b(4, 9, 2);

	//15i−2j+39k
	EXPECT_FLOAT_EQ(Vector3::Cross(a, b).X, -15);
	EXPECT_FLOAT_EQ(Vector3::Cross(a, b).Y, -2);
	EXPECT_FLOAT_EQ(Vector3::Cross(a, b).Z, 39);
}

TEST(LinearAlgebraTests,Vector3_Cross3)
{
	//https://mathinsight.org/cross_product_examples
	Vector3 a(3, -3, 1), b(-12, 12, -4);

	//15i−2j+39k
	EXPECT_FLOAT_EQ(Vector3::Cross(a, b).X, 0);
	EXPECT_FLOAT_EQ(Vector3::Cross(a, b).Y, 0);
	EXPECT_FLOAT_EQ(Vector3::Cross(a, b).Z, 0);
}

TEST(LinearAlgebraTests, Vector3_Dot1)
{
	Vector3 a(1, 2, 3), b(4, -5, 6);
	EXPECT_FLOAT_EQ(Vector3::Dot(a, b), 12);
}

TEST(LinearAlgebraTests, Vector3_Dot2)
{
	Vector3 a(9, 2, 7), b(4, 8, 10);
	EXPECT_FLOAT_EQ(Vector3::Dot(a, b), 122);
}

TEST(LinearAlgebraTests, Vector3_Dot3)
{
	Vector3 a(1, 3, 5), b(4, -2, 1);
	EXPECT_FLOAT_EQ(Vector3::Dot(a, b), 3);
}