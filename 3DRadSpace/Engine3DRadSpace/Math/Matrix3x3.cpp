#include "Matrix3x3.hpp"
#include "Vector2.hpp"
#include "Quaternion.hpp"

using namespace Engine3DRadSpace::Math;

Matrix3x3::Matrix3x3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33):
	M11(m11), M12(m12), M13(m13),
	M21(m21), M22(m22), M23(m23),
	M31(m31), M32(m32), M33(m33)
{
}

Matrix3x3::Matrix3x3(float m[9]):
	M11(m[0]), M12(m[1]), M13(m[2]),
	M21(m[3]), M22(m[4]), M23(m[5]),
	M31(m[6]), M32(m[7]), M33(m[8])
{
}

Matrix3x3 Matrix3x3::CreateTranslation(const Vector2 &t)
{
	return Matrix3x3{
		1, 0, t.X,
		0, 1, t.Y,
		0, 0, 1
	};
}

Matrix3x3 Matrix3x3::CreateScale(const Vector2 &s)
{
	return Matrix3x3{
		s.X, 0, 0,
		0, s.Y, 0,
		0, 0, 1
	};
}

Matrix3x3 Matrix3x3::CreateRotation2D(float theta)
{
	return Matrix3x3{
		cosf(theta), -sinf(theta), 0,
		sinf(theta), cosf(theta), 0,
		0, 0, 1
	};
}

Matrix3x3 Matrix3x3::Create2DSkewing(const Vector2& skewing)
{
	return Matrix3x3(
		1, skewing.X, 0,
		skewing.Y, 1, 0,
		0, 0, 1
	);
}

Matrix3x3 Matrix3x3::CreateRotationX(float alpha)
{
	return Matrix3x3(
		1, 0, 0,
		0, cos(alpha), -sin(alpha),
		0, sin(alpha), cos(alpha)
	);
}

Matrix3x3 Matrix3x3::CreateRotationY(float beta)
{
	return Matrix3x3(
		cos(beta), 0, sin(beta),
		0, 1, 0,
		-sin(beta), 0, cos(beta)
	);
}

Matrix3x3 Matrix3x3::CreateRotationZ(float gamma)
{
	return Matrix3x3(
		cos(gamma), -sin(gamma), 0,
		sin(gamma), cos(gamma), 0,
		0, 0, 1
	);
}

Matrix3x3 Matrix3x3::CreateFromQuaternion(const Quaternion& q)
{
	//https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
	float sqw = q.W * q.W;
	float sqx = q.X * q.X;
	float sqy = q.Y * q.Y;
	float sqz = q.Z * q.Z;

	Matrix3x3 r;

	r.M11 = (sqx - sqy - sqz + sqw);
	r.M22 = (-sqx + sqy - sqz + sqw);
	r.M33 = (-sqx - sqy + sqz + sqw);

	float tmp1 = q.X * q.Y;
	float tmp2 = q.Z * q.W;
	r.M21 = 2.0f * (tmp1 + tmp2);
	r.M12 = 2.0f * (tmp1 - tmp2);

	tmp1 = q.X * q.Z;
	tmp2 = q.Y * q.W;
	r.M31 = 2.0f * (tmp1 - tmp2);
	r.M13 = 2.0f * (tmp1 + tmp2);
	tmp1 = q.Y * q.Z;
	tmp2 = q.X * q.W;
	r.M32 = 2.0f * (tmp1 + tmp2);
	r.M23 = 2.0f * (tmp1 - tmp2);

	return r;
}

float Matrix3x3::Trace() const noexcept
{
	return M11 + M22 + M33;
}

float Matrix3x3::Determinant() const noexcept
{
	//Using Rule of Sarrus
	return M11 * M22 * M33 + M12 * M23 * M31 + M21 * M32 * M13 - M13 * M22 * M31 - M21 * M12 * M33 - M11 * M23 * M32;
}

float& Matrix3x3::operator[](unsigned index)
{
	switch(index)
	{
	case 1: return M11;
	case 2: return M12;
	case 3: return M13;
	case 4: return M21;
	case 5: return M22;
	case 6: return M23;
	case 7: return M31;
	case 8: return M32;
	case 9: return M33;
	default: throw std::out_of_range("0 <= index <= 9");
	}
}

Matrix3x3& Matrix3x3::Hadamard(const Matrix3x3& m)
{
	M11 *= m.M11;
	M12 *= m.M12;
	M13 *= m.M13;

	M21 *= m.M21;
	M22 *= m.M22;
	M23 *= m.M23;

	M31 *= m.M31;
	M32 *= m.M32;
	M33 *= m.M33;

	return *this;
}

Matrix3x3 Matrix3x3::Hadamard(const Matrix3x3& a, const Matrix3x3& b)
{
	return Matrix3x3
	{
		a.M11 * b.M11,
		a.M12 * b.M12,
		a.M13 * b.M13,

		a.M21 * b.M21,
		a.M22 * b.M22,
		a.M23 * b.M23,

		a.M31 * b.M31,
		a.M32 * b.M32,
		a.M33 * b.M33,
	};
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& m) const noexcept
{
	return Matrix3x3
	{
		M11 + m.M11, M12 + m.M12, M13 + m.M13,
		M21 + m.M21, M22 + m.M22, M23 + m.M13,
		M31 + m.M31, M32 + m.M32, M33 + m.M33
	};
}

Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& m) noexcept
{
	M11 += m.M11;
	M12 += m.M12;
	M13 += m.M13;

	M21 += m.M21;
	M22 += m.M22;
	M23 += m.M23;

	M31 += m.M31;
	M32 += m.M32;
	M33 += m.M33;

	return *this;
}

Matrix3x3 Matrix3x3::operator-() const noexcept
{
	return Matrix3x3{
		-M11, -M12, -M13,
		-M21, -M22, -M23,
		-M31, -M32, -M33
	};
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& m) const noexcept
{
	return Matrix3x3{
		M11 - m.M11, M12 - m.M12, M13 - m.M13,
		M21 - m.M21, M22 - m.M22, M23 - m.M23,
		M31 - m.M31, M32 - m.M32, M33 - m.M33
	};
}

Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& m) noexcept
{
	M11 -= m.M11;
	M12 -= m.M12;
	M13 -= m.M13;

	M21 -= m.M21;
	M22 -= m.M22;
	M23 -= m.M23;

	M31 -= m.M31;
	M32 -= m.M32;
	M33 -= m.M33;

	return *this;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& m) const noexcept
{
	return Matrix3x3
	{

		M11 * m.M11 + M12 * m.M21 + M13 * m.M31,
		M11 * m.M12 + M12 * m.M22 + M13 * m.M32,
		M11 * m.M13 + M12 * m.M23 + M13 * m.M33,

		M21 * m.M11 + M22 * m.M21 + M23 * m.M31,
		M21 * m.M12 + M22 * m.M22 + M23 * m.M32,
		M21 * m.M13 + M22 * m.M23 + M23 * m.M33,

		M31 * m.M11 + M32 * m.M21 + M33 * m.M31,
		M31 * m.M12 + M32 * m.M22 + M33 * m.M32,
		M31 * m.M13 + M32 * m.M23 + M33 * m.M33
	};
}

Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& m) noexcept
{
	return *this = (*this) * m;
}

Matrix3x3 Matrix3x3::operator*(float s) const noexcept
{
	return Matrix3x3
	{
		M11 * s, M12 * s, M13 * s,
		M21 * s, M22 * s, M23 * s,
		M31 * s, M32 * s, M33 * s,
	};
}

Matrix3x3& Matrix3x3::operator*=(float s) noexcept
{
	M11 *= s;
	M12 *= s;
	M13 *= s;

	M21 *= s;
	M22 *= s;
	M23 *= s;

	M31 *= s;
	M32 *= s;
	M33 *= s;

	return *this;
}

Matrix3x3 Matrix3x3::operator/(float s) const
{
	return Matrix3x3
	{
		M11 / s, M12 / s, M13 / s,
		M21 / s, M22 / s, M23 / s,
		M31 / s, M32 / s, M33 / s,
	};
}

Matrix3x3& Matrix3x3::operator/=(float s)
{
	M11 /= s;
	M12 /= s;
	M13 /= s;

	M21 /= s;
	M22 /= s;
	M23 /= s;

	M31 /= s;
	M32 /= s;
	M33 /= s;

	return *this;
}

Matrix3x3 Engine3DRadSpace::Math::operator*(float s, const Matrix3x3& m) noexcept
{
	return Matrix3x3
	{
		s * m.M11, s * m.M12, s * m.M13,
		s * m.M21, s * m.M22, s * m.M23,
		s * m.M31, s * m.M32, s * m.M33,
	};
}

Matrix3x3 Engine3DRadSpace::Math::operator/(float s, const Matrix3x3& m)
{
	return Matrix3x3
	{
		s / m.M11, s / m.M12, s / m.M13,
		s / m.M21, s / m.M22, s / m.M23,
		s / m.M31, s / m.M32, s / m.M33,
	};
}
