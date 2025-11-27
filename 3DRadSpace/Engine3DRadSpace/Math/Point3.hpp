#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct E3DRSP_MATH_EXPORT Point3
	{
		constexpr Point3(int x = 0, int y = 0, int z = 0) : X(x), Y(y), Z(z) {};

		int X;
		int Y;
		int Z;

		Point3 operator +=(const Point3& p);
		Point3 operator +(const Point3& p) const;

		Point3 operator -=(const Point3& p);
		Point3 operator -(const Point3& p) const;
		Point3 operator -();

		Point3 operator *=(float s);
		Point3 operator *(float s) const;

		Point3 operator /=(float s);
		Point3 operator /(float s) const;

		auto operator <=>(const Point3&) const noexcept = default;

		operator Engine3DRadSpace::Math::Vector3() const;
	};
}

Engine3DRadSpace::Math::Point3 E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::Point3& p);
