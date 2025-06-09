#include "pch.h"
#include <Engine3DRadSpace/Math/Vector3.hpp>
#include <Engine3DRadSpace/Math/Vector4.hpp>
#include <Engine3DRadSpace/Math/Quaternion.hpp>

using namespace Engine3DRadSpace::Math;

static void expect_equal_vec3(const Vector3& a,const Vector3& b)
{
	EXPECT_FLOAT_EQ(a.X, b.X);
	EXPECT_FLOAT_EQ(a.Y, b.Y);
	EXPECT_FLOAT_EQ(a.Z, b.Z);
}

TEST(LinearAlgebraTests,Vector3_Cross1)
{
	//Basic cross product test:
	Vector3 a = Vector3::UnitX(), b = Vector3::UnitY();

	Vector3 r1 = Vector3::Cross(a, b);
	Vector3 r2 = a.Cross(b);

	expect_equal_vec3(r1, Vector3::UnitZ());
	expect_equal_vec3(r1, r2);
}

TEST(LinearAlgebraTests,Vector3_Cross2)
{
	//https://mathinsight.org/cross_product_examples
	Vector3 a(3, -3, 1), b(4, 9, 2);

	//-15i−2j+39k
	Vector3 r1 = Vector3::Cross(a, b);
	Vector3 r2 = a.Cross(b);
	
	expect_equal_vec3(r1, Vector3(-15, -2, 39));
	expect_equal_vec3(r1, r2);
}

TEST(LinearAlgebraTests,Vector3_Cross3)
{
	//https://mathinsight.org/cross_product_examples
	Vector3 a(3, -3, 1), b(-12, 12, -4);

	//0i+0j+0k
	expect_equal_vec3(Vector3::Cross(a, b), Vector3::Zero());
	expect_equal_vec3(a.Cross(b), Vector3::Zero());
}

TEST(LinearAlgebraTests, Vector3_Dot1)
{
	Vector3 a(1, 2, 3), b(4, -5, 6);
	EXPECT_FLOAT_EQ(Vector3::Dot(a, b), 12);
	EXPECT_FLOAT_EQ(a.Dot(b), 12);
}

TEST(LinearAlgebraTests, Vector3_Dot2)
{
	Vector3 a(9, 2, 7), b(4, 8, 10);
	EXPECT_FLOAT_EQ(Vector3::Dot(a, b), 122);
	EXPECT_FLOAT_EQ(a.Dot(b), 122);
}

TEST(LinearAlgebraTests, Vector3_Dot3)
{
	Vector3 a(1, 3, 5), b(4, -2, 1);
	EXPECT_FLOAT_EQ(Vector3::Dot(a, b), 3);
	EXPECT_FLOAT_EQ(a.Dot(b), 3);
}

TEST(LinearAlgebraTests, Vector3_TransformQuaternion1)
{
	//https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/transforms/index.htm
	Quaternion q = Quaternion::FromYawPitchRoll(0, 0, 0);
	Vector3 v(1, 0, 0);
	Vector3 r1 = v.Transform(q);
	expect_equal_vec3(r1, Vector3(1, 0, 0));

	Vector3 r2 = Vector3::Transform(v,q);

	expect_equal_vec3(r2, r1);
}

TEST(LinearAlgebraTests, Vector3_TransformQuaternion2)
{
	//TODO: Why negative?
	Quaternion q = Quaternion::FromYawPitchRoll(-std::numbers::pi_v<float> / 2, 0, 0);
	Vector3 v(1, 0, 1);

	Vector3 r1 = Vector3(v).Transform(q);
	expect_equal_vec3(r1, Vector3(-1, 0, 1));

	Vector3 r2 = Vector3::Transform(v,q);
	expect_equal_vec3(r2, r1);
}

TEST(LinearAlgebraTests, Vector3_TransformQuaternion3)
{
	Quaternion q = Quaternion::FromYawPitchRoll( -std::numbers::pi_v<float> / 2, 0, 0); //90 degrees ccw on Y axis
	Vector3 v(1, 0, 0);

	Vector3 r1 = Vector3(v).Transform(q);
	expect_equal_vec3(r1, Vector3(0, 0, 1));

	Vector3 r2 = Vector3::Transform(v, q);
	expect_equal_vec3(r2, r1);
}