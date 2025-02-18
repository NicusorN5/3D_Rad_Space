/// ------------------------------------------------------------------------------------------------
/// File:   Math/Point.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "../Libs.hpp"
#include "Vector2.hpp"

namespace Engine3DRadSpace
{
	namespace Math
	{
		struct DLLEXPORT Point
		{
			constexpr Point(int x = 0, int y = 0) : X(x), Y(y) {};

			int X;
			int Y;

			Point operator +=(const Point& p);
			Point operator +(const Point &p) const;

			Point operator -=(const Point& p);
			Point operator -(const Point &p) const;
			Point operator -();

			Point operator *=(float s);
			Point operator *(float s) const;

			Point operator /=(float s);
			Point operator /(float s) const;

			auto operator <=>(const Point&) const noexcept = default;

			operator Engine3DRadSpace::Math::Vector2() const;
		};
	}
}

Engine3DRadSpace::Math::Point DLLEXPORT operator * (float s, const Engine3DRadSpace::Math::Point& p);

