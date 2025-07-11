#include "Quaternion.hpp"
#include "Matrix4x4.hpp"

using namespace Engine3DRadSpace::Math;

Quaternion Quaternion::FromYawPitchRoll(float yaw, float pitch, float roll)
{
	//https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
	//https://github.com/labnation/MonoGame/blob/master/MonoGame.Framework/Quaternion.cs
	Quaternion r;
	
	float num9 = roll * 0.5f;
	float num6 = (float)sin((double)num9);
	float num5 = (float)cos((double)num9);
	float num8 = pitch * 0.5f;
	float num4 = (float)sin((double)num8);
	float num3 = (float)cos((double)num8);
	float num7 = yaw * 0.5f;
	float num2 = (float)sin((double)num7);
	float num = (float)cos((double)num7);
	r.X = ((num * num4) * num5) + ((num2 * num3) * num6);
	r.Y = ((num2 * num3) * num5) - ((num * num4) * num6);
	r.Z = ((num * num3) * num6) - ((num2 * num4) * num5);
	r.W = ((num * num3) * num5) + ((num2 * num4) * num6);
	
	return r;
}

Quaternion Quaternion::FromAxisAngle(const Vector3& axis, float angle)
{
	float w = cos(angle / 2.0f);
	float x = axis.X * sin(angle / 2.0f);
	float y = axis.Y * sin(angle / 2.0f);
	float z = axis.Z * sin(angle / 2.0f);

	return Quaternion(x, y, z, w);
}

Quaternion Quaternion::FromMatrix(const Matrix4x4& m)
{
	Quaternion q;

	float tr = m.Trace();

	float m00 = m.M11, m01 = m.M12, m02 = m.M13;
	float m10 = m.M21, m11 = m.M22, m12 = m.M23;
	float m20 = m.M31, m21 = m.M32, m22 = m.M33;

	if (tr > 0) {
		float S = sqrtf(tr + 1.0f) * 2; // S=4*qw 
		q.W = 0.25f * S;
		q.X = (m21 - m12) / S;
		q.Y = (m02 - m20) / S;
		q.Z = (m10 - m01) / S;
	}
	else if ((m00 > m11) && (m00 > m22)) {
		float S = sqrtf(1.0f + m00 - m11 - m22) * 2; // S=4*qx 
		q.W = (m21 - m12) / S;
		q.X = 0.25f * S;
		q.Y = (m01 + m10) / S;
		q.Z = (m02 + m20) / S;
	}
	else if (m11 > m22) {
		float S = sqrtf(1.0f + m11 - m00 - m22) * 2; // S=4*qy
		q.W = (m02 - m20) / S;
		q.X = (m01 + m10) / S;
		q.Y = 0.25f * S;
		q.Z = (m12 + m21) / S;
	}
	else {
		float S = sqrtf(1.0f + m22 - m00 - m11) * 2; // S=4*qz
		q.W = (m10 - m01) / S;
		q.X = (m02 + m20) / S;
		q.Y = (m12 + m21) / S;
		q.Z = 0.25f * S;
	}
	return q;
}

Quaternion Quaternion::FromVectorToVector(const Vector3& a, const Vector3& b)
{
	Quaternion q;
	Vector3 c = Vector3::Cross(a, b);

	q.X = c.X;
	q.Y = c.Y;
	q.Z = c.Z;
	q.W = 1 + Vector3::Dot(a, b);

	return q.Normalize();
}

float Quaternion::Length() const noexcept
{
	return sqrtf((X * X) + (Y * Y) + (Z * Z) + (W * W));
}

float Quaternion::LengthSquared() const noexcept
{
	return (X * X) + (Y * Y) + (Z * Z) + (W * W);
}

Quaternion& Quaternion::Normalize()
{
	*this /= Length();
	return *this;
}

Quaternion& Quaternion::Conjugate() noexcept
{
	this->X *= -1;
	this->Y *= -1;
	this->Z *= -1;
	return *this;
}

Quaternion& Quaternion::Inverse()
{
	float invdot = 1.0f / Dot(*this);
	X = -X * invdot;
	Y = -Y * invdot;
	Z = -Z * invdot;
	W = W * invdot;
	return *this;
}

float Quaternion::Dot(const Quaternion& q) const noexcept
{
	return X * q.X + Y * q.Y + Z * q.Z + W * q.W;
}

float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
{
	return a.X * b.X + a.Y * b.Y + a.Z * b.Z + a.W * b.W;
}

float& Quaternion::Re() noexcept
{
	return W;
}

float Quaternion::Re() const noexcept
{
	return W;
}

Vector3 Quaternion::Im() const noexcept
{
	return Vector3(X,Y,Z);
}

Vector3 Quaternion::ToYawPitchRoll() const
{
	//https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
	Vector3 r;

	// yaw (Y-axis rotation)
	float siny_cosp = 2 * (W * Z + X * Y);
	float cosy_cosp = 1 - 2 * (Y * Y + Z * Z);
	r.Y = std::atan2f(siny_cosp, cosy_cosp);

	// pitch (x-axis rotation)
	float sinp = std::sqrtf(1 + 2 * (W * Y - X * Z));
	float cosp = std::sqrtf(1 - 2 * (W * Y - X * Z));
	r.X = 2.0f * std::atan2f(sinp, cosp) - std::numbers::pi_v<float> / 2.0f;

	// roll (z-axis rotation)
	float sinr_cosp = 2 * (W * X + Y * Z);
	float cosr_cosp = 1 - 2 * (X * X + Y * Y);
	r.Z = std::atan2f(sinr_cosp, cosr_cosp);

	return r;
}

Quaternion& Quaternion::Hadamard(const Quaternion& q)
{
	X *= q.X;
	Y *= q.Y;
	Z *= q.Z;
	W *= q.W;
	return *this;
}

Quaternion& Quaternion::operator-() noexcept
{
	X *= -1;
	Y *= -1;
	Z *= -1;
	W *= -1;
	return *this;
}

Quaternion Quaternion::operator+(const Quaternion &q) const noexcept
{
	return Quaternion
	{
		X + q.X,
		Y + q.Y,
		Z + q.Z,
		W + q.W
	};
}

Quaternion& Quaternion::operator+=(const Quaternion &q) noexcept
{
	X += q.X;
	Y += q.Y;
	Z += q.Z;
	W += q.W;

	return *this;
}

Quaternion Quaternion::operator-(const Quaternion& q) const noexcept
{
	return Quaternion{
		X - q.X,
		Y - q.Y,
		Z - q.Z,
		W - q.W,
	};
}

Quaternion& Quaternion::operator -=(const Quaternion& q) noexcept
{
	X -= q.X;
	Y -= q.Y;
	Z -= q.Z;
	W -= q.W;

	return *this;
}

Quaternion Quaternion::operator*(const Quaternion& q) const noexcept
{
	//https://stackoverflow.com/questions/19956555/how-to-multiply-two-quaternions
	Quaternion r;

	r.W = W * q.W - X * q.X - Y * q.Y - Z * q.Z;  // 1
	r.X = W * q.X + X * q.W + Y * q.Z - Z * q.Y;  // i
	r.Y = W * q.Y - X * q.Z + Y * q.W + Z * q.X;  // j
	r.Z = W * q.Z + X * q.Y - Y * q.Z + Z * q.W;  // k

	return r;
}

Quaternion& Quaternion::operator*=(const Quaternion &q) noexcept
{
	Quaternion cpy;
	cpy.W = W * q.W - X * q.X - Y * q.Y - Z * q.Z;
	cpy.X = W * q.X + X * q.W + Y * q.Z - Z * q.Y;
	cpy.Y = W * q.Y - X * q.Z + Y * q.W + Z * q.X;
	cpy.Z = W * q.Z + X * q.Y - Y * q.Z + Z * q.W;

	return *this = cpy;
}

Quaternion Quaternion::operator*(float s) const noexcept
{
	return Quaternion(
		X * s,   
		Y * s,   
		Z * s,   
		W * s  
	);
}

Quaternion& Quaternion::operator*=(float s) noexcept
{
	X *= s;
	Y *= s;
	Z *= s;
	W *= s;
	return *this;
}

Quaternion Quaternion::operator/(float s) const
{
	return Quaternion(
		this->X / s,
		this->Y / s,
		this->Z / s,
		this->W / s);
}

Quaternion& Quaternion::operator/=(float s)
{
	X /= s;
	Y /= s;
	Z /= s;
	W /= s;

	return *this;
}

Quaternion Engine3DRadSpace::Math::operator/(float f, const Quaternion& q)
{
	return Quaternion
	{
		f / q.X,
		f / q.Y,
		f / q.Z,
		f / q.W
	};
}

Quaternion Engine3DRadSpace::Math::operator*(float s, const Quaternion& q) noexcept
{
	return Quaternion
	{
		q.X * s,
		q.Y * s,
		q.Z * s,
		q.W * s,
	};
}
