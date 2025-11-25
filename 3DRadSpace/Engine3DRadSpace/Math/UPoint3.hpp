#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct E3DRSP_MATH_EXPORT UPoint3
	{
		constexpr UUPoint3(
			unsigned x = 0,
			unsigned y = 0,
			unsigned z = 0
		) :X(x), Y(y), Z(z) 
		{
		};

		unsigned X;
		unsigned Y;
		unsigned Z;

		UPoint3 operator +=(const UPoint3& p);
		UPoint3 operator +(const UPoint3& p) const;

		UPoint3 operator -=(const UPoint3& p);
		UPoint3 operator -(const UPoint3& p) const;

		UPoint3 operator *=(float s);
		UPoint3 operator *(float s) const;

		UPoint3 operator /=(float s);
		UPoint3 operator /(float s) const;

		auto operator <=>(const UPoint3&) const noexcept = default;
	};
}

Engine3DRadSpace::Math::UPoint3 E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::UPoint3& p);
