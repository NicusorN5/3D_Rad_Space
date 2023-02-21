#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace::Math
{
	struct Vector2
	{
		float X, Y;
		Vector2(float x = 0.0f, float y = 0.0f) :X(x), Y(y) {};

		float Length() const;
		float Angle() const;
		
		float Dot(const Vector2 &v) const;

		Vector2& operator +=(const Vector2& v);
		Vector2 operator +(const Vector2& v);

		Vector2& operator-();
		Vector2& operator -=(const Vector2& v);
		Vector2 operator -(const Vector2& v);

		float operator*(const Vector2& v);
		Vector2 operator*(float s);
		Vector2& operator *=(float s);

		auto operator <=>(const Vector2& v) const = default;
	};
}

Engine3DRadSpace::Math::Vector2 operator*(float s, const Engine3DRadSpace::Math::Vector2& v);