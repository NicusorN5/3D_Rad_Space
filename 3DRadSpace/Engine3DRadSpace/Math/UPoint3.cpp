#include "UPoint3.hpp"

using namespace Engine3DRadSpace::Math;

UPoint3 UPoint3::operator+=(const UPoint3& p)
{
	this->X += p.X;
	this->Y += p.Y;
	this->Z += p.Z;
	return *this;
}

UPoint3 UPoint3::operator+(const UPoint3& p) const
{
	return UPoint3(
		this->X + p.X,
		this->Y + p.Y,
		this->Z + p.Z
	);
}

UPoint3 UPoint3::operator-=(const UPoint3& p)
{
	this->X -= p.X;
	this->Y -= p.Y;
	this->Z -= p.Z;
	return *this;
}

UPoint3 UPoint3::operator-(const UPoint3& p) const
{
	return UPoint3(
		this->X - p.X,
		this->Y - p.Y,
		this->Z - p.Z
	);
}

#pragma warning(push)
#pragma warning(disable : 4244)
UPoint3 UPoint3::operator*=(float s)
{
	this->X *= s;
	this->Y *= s;
	this->Z *= s;
	return *this;
}

UPoint3 UPoint3::operator*(float s) const
{
	return UPoint3(
		int(this->X * s ),
		int(this->Y * s),
		int(this->Z * s)
	);
}

UPoint3 UPoint3::operator/=(float s)
{
	this->X /= s;
	this->Y /= s;
	this->Z /= s;
	return *this;
}
#pragma warning(pop)

UPoint3 UPoint3::operator/(float s) const
{
	return UPoint3(
		int(this->X / s),
		int(this->Y / s),
		int(this->Z / s)
	);
}

UPoint3 operator*(float s, const UPoint3& p)
{
	return UPoint3(
		int(s * p.X),
		int(s * p.Y),
		int(s * p.Z)
	);
}

UPoint3 operator/(float s, const UPoint3& p)
{
	return UPoint3(
		int(s / p.X),
		int(s / p.Y),
		int(s / p.Z)
	);
}