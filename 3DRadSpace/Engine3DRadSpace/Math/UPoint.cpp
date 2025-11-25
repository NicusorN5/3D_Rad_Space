#include "UPoint.hpp"

using namespace Engine3DRadSpace::Math;

UPoint UPoint::operator+=(const UPoint& p)
{
    this->X += p.X;
    this->Y += p.Y;
    return *this;
}

UPoint UPoint::operator+(const UPoint& p) const
{
    return UPoint(this->X + p.X, this->Y + p.Y);
}

UPoint UPoint::operator-=(const UPoint& p)
{
    this->X -= p.X;
    this->Y -= p.Y;
    return *this;
}

UPoint UPoint::operator-(const UPoint& p) const
{
    return UPoint(this->X - p.X, this->Y - p.Y);
}

#pragma warning(push)
#pragma warning(disable : 4244)
UPoint UPoint::operator*=(float s)
{
    this->X *= s;
    this->Y *= s;
    return *this;
}

UPoint UPoint::operator*(float s) const
{
    return UPoint(int(this->X * s ),int(this->Y * s));
}

UPoint UPoint::operator/=(float s)
{
    this->X /= s;
    this->Y /= s;
    return *this;
}
#pragma warning(pop)

UPoint UPoint::operator/(float s) const
{
    return UPoint(int(this->X / s), int(this->Y / s));
}

UPoint operator*(float s, const UPoint& p)
{
    return UPoint(int(s * p.X), int(s * p.Y));
}

UPoint operator/(float s, const UPoint& p)
{
    return UPoint(int(s / p.X), int(s / p.Y));
}