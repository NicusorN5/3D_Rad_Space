#pragma once
#include "../Core/Libs.hpp"
#include "Vector4.hpp"

namespace Engine3DRadSpace::Math
{
	struct E3DRSP_MATH_EXPORT Point4
	{
		constexpr Point4(int x = 0, int y = 0, int z = 0, int w = 0) : X(x), Y(y), Z(z), W(w) {};

		int X;
		int Y;
		int Z;
		int W;

		Point4 operator +=(const Point4& p);
		Point4 operator +(const Point4& p) const;

		Point4 operator -=(const Point4& p);
		Point4 operator -(const Point4& p) const;
		Point4 operator -();

		Point4 operator *=(float s);
		Point4 operator *(float s) const;

		Point4 operator /=(float s);
		Point4 operator /(float s) const;

		auto operator <=>(const Point4&) const noexcept = default;

		operator Engine3DRadSpace::Math::Vector4() const;
	};
}

Engine3DRadSpace::Math::Point4 E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::Point4& p);
