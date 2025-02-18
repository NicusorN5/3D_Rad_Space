/// ------------------------------------------------------------------------------------------------
/// File:   Math/Vector3.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "Vector3.hpp"

using namespace Engine3DRadSpace::Math;

Vector3 Vector3::Zero()
{
    return Vector3(0, 0, 0);
}

Vector3 Vector3::UnitX()
{
    return Vector3(1, 0, 0);
}

Vector3 Vector3::UnitY()
{
    return Vector3(0, 1, 0);
}

Vector3 Vector3::UnitZ()
{
    return Vector3(0, 0, 1);
}

Vector3 Vector3::One()
{
    return Vector3(1,1,1);
}

Vector3 Vector3::Up()
{
    return Vector3{ 0, 1, 0 };
}

Vector3 Vector3::Down()
{
    return Vector3{ 0, -1, 0 };
}

Vector3 Vector3::Forward()
{
    return Vector3{ 0, 0, -1 };
}

Vector3 Vector3::Backward()
{
    return Vector3{ 0, 0, 1 };
}

Vector3 Vector3::Left()
{
    return Vector3{ -1, 0, 0 };
}

Vector3 Vector3::Right()
{
    return Vector3{ 1, 0,0 };
}

float Vector3::Length() const
{
    return sqrtf((X * X) + (Y * Y) + (Z * Z));
}

float Vector3::LengthSquared() const
{
    return (X * X) + (Y * Y) + (Z * Z);
}

Vector3& Vector3::Normalize()
{
    float l = this->Length();

    this->X /= l;
    this->Y /= l;
    this->Z /= l;

    return *this;
}

Vector3 Engine3DRadSpace::Math::Vector3::Normalize(const Vector3& v)
{
    float l = v.Length();
    return { v.X / l, v.Y / l, v.Z / l };
}

Vector3& Vector3::operator+=(const Vector3& v)
{
    this->X += v.X;
    this->Y += v.Y;
    this->Z += v.Z;
    return *this;
}

Vector3 Vector3::operator+(const Vector3& v) const
{
    return Vector3{ X + v.X, Y + v.Y, Z + v.Z };
}

Vector3& Vector3::operator-=(const Vector3& v)
{
    this->X -= v.X;
    this->Y -= v.Z;
    this->Z -= v.Z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& v) const
{
    return Vector3(this->X - v.X, this->Y - v.Y, this->Z - v.Z);
}

Vector3& Vector3::operator-()
{
    this->X *= -1;
    this->Y *= -1;
    this->Z *= -1;
    return *this;
}

Vector3 Engine3DRadSpace::Math::Vector3::operator-() const
{
    Vector3 c(*this);
    c.X *= 1;
    c.Y *= 1;
    c.Z *= 1;

    return c;
}

Vector3& Vector3::operator*=(float s)
{
    this->X *= s;
    this->Y *= s;
    this->Z *= s;
    return *this;
}

Vector3 Vector3::operator*(float s) const
{
    return Vector3(s * this->X, s * this->Y, s * this->Z);
}

Vector3& Vector3::operator/=(float s)
{
    X /= s;
    Y /= s;
    Z /= s;
    return *this;
}

Vector3 Vector3::operator/(float s) const
{
    return Vector3(
        X / s,
        Y / s,
        Z / s
    );
}

Vector3 Vector3::Cross(const Vector3& v)
{
    Vector3 cpy(*this);
    cpy.X = Y * v.Z - Z * v.Y;
    cpy.Y = Z * v.X - X * v.Z;
    cpy.Z = X * v.Y - Y * v.X;

    return *this = cpy;
}

Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2)
{
    return Vector3(
        v1.Y * v2.Z - v1.Z * v2.Y,
        v1.Z * v2.X - v1.X * v2.Z,
        v1.X * v2.Y - v1.Y * v2.X
    );
}

float Vector3::Dot(const Vector3& v) const
{
    return (this->X * v.X) + (this->Y * v.Y) + (this->Z * v.Z);
}

float Vector3::Dot(const Vector3& a, const Vector3& b)
{
    return (a.X * b.X) + (a.Y + b.Y) + (a.Z * b.Z);
}

Vector3& Vector3::Transform(const Quaternion& q)
{
    Vector3 v(*this);

     // Extract the vector part of the quaternion
    Vector3 u(q.Im());

    // Extract the scalar part of the quaternion
    float s = q.W;

    // Do the math
    auto vprime = 2.0f * Dot(u, v) * u
           + (s*s - Dot(u, u)) * v
           + 2.0f * s * Cross(u, v);

    return *this = vprime;
}

Vector3& Vector3::Transform(const Matrix4x4& m)
{
    Vector3 cpy(*this);

    this->X = cpy.X * m.M11 + cpy.Y * m.M12 + cpy.Z * m.M13 + m.M14;
    this->Y = cpy.X * m.M21 + cpy.Y * m.M22 + cpy.Z * m.M23 + m.M24;
    this->Z = cpy.X * m.M31 + cpy.Y * m.M32 + cpy.Z * m.M33 + m.M34;

    return *this;
}

Vector3 Vector3::Transform(const Vector3& v, const Quaternion& q)
{
    return Vector3(v).Transform(q);
}

Vector3 Vector3::Transform(const Vector3& v, const Matrix4x4& m)
{
    return Vector3{
        v.X * m.M11 + v.Y * m.M12 + v.Z * m.M13 + m.M14,
        v.X * m.M21 + v.Y * m.M22 + v.Z * m.M23 + m.M24,
        v.X * m.M31 + v.Y * m.M32 + v.Z * m.M33 + m.M34,
    };
}

Vector3& Vector3::Hadamard(const Vector3& v)
{
    X *= v.X;
    Y *= v.Y;
    Z *= v.Z;
    return *this;
}

Vector3 Vector3::Hadamard(const Vector3& a, const Vector3& b)
{
    return Vector3
    {
        a.X * b.X,
        a.Y * b.Y,
        a.Z * b.Z
    };
}

Vector3 Engine3DRadSpace::Math::operator*(float s, const Vector3& v)
{
    return Vector3{ s * v.X, s * v.Y, s * v.Z };
}

Vector3 Engine3DRadSpace::Math::operator/(float s, const Vector3 &v)
{
    return Vector3{ s / v.X, s / v.Y, s / v.Z };
}
