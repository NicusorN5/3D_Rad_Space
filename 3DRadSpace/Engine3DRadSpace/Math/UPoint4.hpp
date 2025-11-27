#pragma once
#include "../Core/Libs.hpp"
#include "Vector4.hpp"

namespace Engine3DRadSpace::Math
{
	struct E3DRSP_MATH_EXPORT UPoint4
	{
		constexpr UPoint4(
			unsigned x = 0,
			unsigned y = 0,
			unsigned z = 0,
			unsigned w = 0
		) : X(x), Y(y), Z(z), W(w) 
		{
		}
		
		unsigned X;
		unsigned Y;
		unsigned Z;
		unsigned W;

		UPoint4 operator +=(const UPoint4& p);
		UPoint4 operator +(const UPoint4& p) const;

		UPoint4 operator -=(const UPoint4& p);
		UPoint4 operator -(const UPoint4& p) const;

		UPoint4 operator *=(float s);
		UPoint4 operator *(float s) const;

		UPoint4 operator /=(float s);
		UPoint4 operator /(float s) const;

		auto operator <=>(const UPoint4&) const noexcept = default;
	};
}

Engine3DRadSpace::Math::UPoint4 E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::UPoint4& p);
