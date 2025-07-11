#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Math
{
	struct Matrix3x3;
	/// <summary>
	/// A 2D vector.
	/// </summary>
	struct E3DRSP_MATH_EXPORT Vector2
	{
		float X, Y;

		Vector2(float x = 0.0f, float y = 0.0f) :X(x), Y(y) {};

		static Vector2 Zero();
		static Vector2 UnitX();
		static Vector2 UnitY();
		static Vector2 One();

		float Length() const;
		float LengthSquared() const;
		float Angle() const;
		
		float Dot(const Vector2 &v) const;
		static float Dot(const Vector2& a, const Vector2& b);
		
		Vector2& Normalize();
		static Vector2 Normalize(const Vector2& v);

		Vector2& operator +=(const Vector2& v);
		Vector2 operator +(const Vector2 &v) const;

		Vector2& operator-();
		Vector2 operator-() const;

		Vector2& operator -=(const Vector2& v);
		Vector2 operator -(const Vector2 &v) const;

		float operator*(const Vector2 &v) const;
		Vector2 operator*(float s) const;
		Vector2& operator *=(float s);

		Vector2& operator /=(float f);
		Vector2 operator /(float f) const;

		static Vector2 ConvertFromNormalizedScreenSpaceToClipSpace(const Vector2& norm);
		static Vector2 ConvertFromScreenCoordsToClipSpace(const Vector2& point, const Vector2& resolution);

		Vector2& RotateBy(float theta);
		Vector2 Rotate(const Vector2 &v, float theta);

		Vector2& Hadamard(const Vector2& v);
		static Vector2 Hadamard(const Vector2& a, const Vector2& b);

		Vector2& Transform(const Matrix3x3& m);
		static Vector2 Transform(const Vector2& v, const Matrix3x3& m);
	};

	Vector2 E3DRSP_MATH_EXPORT operator*(float s, const Vector2& v);
	Vector2 E3DRSP_MATH_EXPORT operator/(float s, const Vector2& v);
}