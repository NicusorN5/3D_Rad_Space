#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Math
{
	struct Vector3;
	struct Quaternion;
	struct Point;

	struct E3DRSP_MATH_EXPORT Matrix4x4
	{
		float M11, M12, M13, M14;
		float M21, M22, M23, M24;
		float M31, M32, M33, M34;
		float M41, M42, M43, M44;

		constexpr explicit Matrix4x4(float m[16]);
		constexpr explicit Matrix4x4(
			float m11 = 1, float m12 = 0, float m13 = 0, float m14 = 0,
			float m21 = 0, float m22 = 1, float m23 = 0, float m24 = 0,
			float m31 = 0, float m32 = 0, float m33 = 1, float m34 = 0,
			float m41 = 0, float m42 = 0, float m43 = 0, float m44 = 1);
		
		static Matrix4x4 CreateTranslation(const Vector3 &pos);
		static Matrix4x4 CreateScale(const Vector3 &scale);

		static Matrix4x4 CreateRotationX(float theta);
		static Matrix4x4 CreateRotationY(float theta);
		static Matrix4x4 CreateRotationZ(float theta);
		static Matrix4x4 CreateFromQuaternion(const Quaternion& q);
		static Matrix4x4 CreateRotationYawPitchRoll(float yaw, float pitch, float roll);

		/// <summary>
		/// Creates a right-hand look at view matrix.
		/// </summary>
		/// <param name="pos">Camera position</param>
		/// <param name="look_at">Camera look direction</param>
		/// <param name="up_dir">Camera normal</param>
		/// <returns>RH View matrix</returns>
		static Matrix4x4 CreateLookAtView(const Vector3 &pos,const Vector3 &look_at,const Vector3 &up_dir);

		static Matrix4x4 CreatePerspectiveProjection(float aspectRatio, float FOV, float npd, float fpd);
		static Matrix4x4 CreateOrthographicProjection(const Point &screenSize, float npd, float fpd);

		static Matrix4x4 CreateSphericalBillboard(const Vector3 &objectPos,const Vector3 &cameraPos,const Vector3 &cameraUp,const Vector3 &cameraForward);
		static Matrix4x4 CreateCilindricalBillboard(const Vector3& objectPos, const Vector3& cameraPos, const Vector3& cameraUp, const Vector3& cameraForward, const Vector3& axis, std::optional<Vector3> objectForward);

		///Element-wise product.
		static Matrix4x4 Hadamard(const Matrix4x4& a, const Matrix4x4& b);
		Matrix4x4& Hadamard(const Matrix4x4& m);

		Matrix4x4 operator +(const Matrix4x4& m) const noexcept;
		Matrix4x4 operator +=(const Matrix4x4& m) noexcept;

		Matrix4x4 operator -(const Matrix4x4& m) const noexcept;
		Matrix4x4 operator -=(const Matrix4x4& m) noexcept;

		Matrix4x4 operator *(const Matrix4x4& m) const noexcept;
		Matrix4x4& operator *=(const Matrix4x4& m) noexcept;

		Matrix4x4 operator*(float scalar) const noexcept;
		Matrix4x4& operator *=(float scalar) noexcept;

		Matrix4x4& Transpose();
		static Matrix4x4 Transpose(const Matrix4x4& m);

		Matrix4x4& Invert();
		static Matrix4x4 Invert(const Matrix4x4& m);

		float& operator[](unsigned index);

		float Trace() const noexcept;
		float Determinant() const noexcept;

		Vector3 Forward() const noexcept;
		Vector3 Backward() const noexcept;

		Vector3 Up() const noexcept;
		Vector3 Down() const noexcept;

		Vector3 Left() const noexcept;
		Vector3 Right() const noexcept;

		Vector3 Translation() const noexcept;
	};

	Matrix4x4 E3DRSP_MATH_EXPORT operator *(float scalar, const Matrix4x4& m) noexcept;
	Matrix4x4 E3DRSP_MATH_EXPORT operator /(float f, const Matrix4x4& m);
}
