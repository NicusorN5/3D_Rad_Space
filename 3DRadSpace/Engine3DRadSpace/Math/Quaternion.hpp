#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct Vector3;
	struct Matrix4x4;

	/// <summary>
	/// A quaternion is a hyper-complex number that represents 3D rotations the same way 2D rotations can be represented by a complex number.
	/// </summary>
	struct DLLEXPORT Quaternion
	{
		float X, Y, Z, W;

		Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : X(x), Y(y), Z(z), W(w) {};

		static Quaternion FromYawPitchRoll(float yaw, float pitch, float roll);
		static Quaternion FromAxisAngle(const Vector3& axis, float angle);
		static Quaternion FromMatrix(const Matrix4x4& m);
		static Quaternion FromVectorToVector(const Vector3& a, const Vector3& b);

		float Length() const noexcept;
		float LengthSquared() const noexcept;
		Quaternion& Normalize();
		Quaternion& Conjugate() noexcept;
		Quaternion& Inverse();

		float Dot(const Quaternion& q) const noexcept;
		static float Dot(const Quaternion& a, const Quaternion& b);

		float& Re() noexcept;
		float Re() const noexcept;
		Vector3 Im() const noexcept;
		
		Vector3 ToYawPitchRoll() const;

		Quaternion& Hadamard(const Quaternion& q);

		Quaternion& operator-() noexcept;

		Quaternion operator +(const Quaternion& q) const noexcept;
		Quaternion& operator +=(const Quaternion& q) noexcept;

		Quaternion operator -(const Quaternion& q) const noexcept;
		Quaternion& operator -=(const Quaternion& q) noexcept;

		Quaternion operator *(const Quaternion& q) const noexcept;
		Quaternion& operator *=(const Quaternion& q) noexcept;

		Quaternion operator*(float s) const noexcept;
		Quaternion& operator *=(float s) noexcept;

		Quaternion operator /(float s) const;
		Quaternion& operator /=(float s);

		auto operator <=>(const Quaternion& q) const noexcept = default;
	};

	Quaternion DLLEXPORT operator /(float f, const Quaternion& q);
	Quaternion DLLEXPORT operator *(float s, const Quaternion& q) noexcept;
}

