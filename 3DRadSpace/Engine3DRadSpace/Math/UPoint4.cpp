#include "UPoint4.hpp"

using namespace Engine3DRadSpace::Math;

UPoint4 UPoint4::operator+=(const UPoint4& p)
{
	this->X += p.X;
	this->Y += p.Y;
	this->Z += p.Z;
	this->W += p.W;
	return *this;
}

UPoint4 UPoint4::operator+(const UPoint4& p) const
{
	return UPoint4(
		this->X + p.X,
		this->Y + p.Y,
		this->Z + p.Z,
		this->W + p.W
	);
}

UPoint4 UPoint4::operator-=(const UPoint4& p)
{
	this->X -= p.X;
	this->Y -= p.Y;
	this->Z -= p.Z;
	this->W -= p.W;
	return *this;
}

UPoint4 UPoint4::operator-(const UPoint4& p) const
{
	return UPoint4(
		this->X - p.X,
		this->Y - p.Y,
		this->Z - p.Z,
		this->W - p.W
	);
}

#pragma warning(push)
#pragma warning(disable : 4244)
UPoint4 UPoint4::operator*=(float s)
{
	this->X *= s;
	this->Y *= s;
	this->Z *= s;
	this->W *= s;
	return *this;
}

UPoint4 UPoint4::operator*(float s) const
{
	return UPoint4(
		int(this->X * s),
		int(this->Y * s),
		int(this->Z * s),
		int(this->W * s)
	);
}

UPoint4 UPoint4::operator/=(float s)
{
	this->X /= s;
	this->Y /= s;
	this->Z /= s;
	this->W /= s;
	return *this;
}
#pragma warning(pop)

UPoint4 UPoint4::operator/(float s) const
{
	return UPoint4(
		int(this->X / s),
		int(this->Y / s),
		int(this->Z / s),
		int(this->W / s)
	);
}

UPoint4 operator*(float s, const UPoint4& p)
{
	return UPoint4(
		int(s * p.X),
		int(s * p.Y),
		int(s * p.Z),
		int(s * p.W)
	);
}

UPoint4 operator/(float s, const UPoint4& p)
{
	return UPoint4(
		int(s / p.X),
		int(s / p.Y),
		int(s / p.Z),
		int(s / p.W)
	);
}