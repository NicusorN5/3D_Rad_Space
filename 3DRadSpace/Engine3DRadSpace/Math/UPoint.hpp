#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace
{
	namespace Math
	{
		struct E3DRSP_MATH_EXPORT UPoint
		{
			constexpr UPoint(unsigned x = 0, unsigned y = 0) : X(x), Y(y) {};

			unsigned X;
			unsigned Y;

			UPoint operator +=(const UPoint& p);
			UPoint operator +(const UPoint&p) const;

			UPoint operator -=(const UPoint& p);
			UPoint operator -(const UPoint&p) const;

			UPoint operator *=(float s);
			UPoint operator *(float s) const;

			UPoint operator /=(float s);
			UPoint operator /(float s) const;

			auto operator <=>(const UPoint&) const noexcept = default;
		};
	}
}

Engine3DRadSpace::Math::UPoint E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::UPoint& p);

