#include "Point4.hpp"

using namespace Engine3DRadSpace::Math;

Point4 Point4::operator+=(const Point4& p)
{
	this->X += p.X;
	this->Y += p.Y;
	this->Z += p.Z;
	this->W += p.W;
	return *this;
}

Point4 Point4::operator+(const Point4& p) const
{
	return Point4(
		this->X + p.X,
		this->Y + p.Y,
		this->Z + p.Z,
		this->W + p.W
	);
}

Point4 Point4::operator-=(const Point4& p)
{
	this->X -= p.X;
	this->Y -= p.Y;
	this->Z -= p.Z;
	this->W -= p.W;
	return *this;
}

Point4 Point4::operator-(const Point4& p) const
{
	return Point4(
		this->X - p.X,
		this->Y - p.Y,
		this->Z - p.Z,
		this->W - p.W
	);
}

Point4 Point4::operator-()
{
	this->X *= -1;
	this->Y *= -1;
	this->Z *= -1;
	this->W *= -1;
	return *this;
}

#pragma warning(push)
#pragma warning(disable : 4244)
Point4 Point4::operator*=(float s)
{
	this->X *= s;
	this->Y *= s;
	this->Z *= s;
	this->W *= s;
	return *this;
}

Point4 Point4::operator*(float s) const
{
	return Point4(
		int(this->X * s),
		int(this->Y * s),
		int(this->Z * s),
		int(this->W * s)
	);
}

Point4 Point4::operator/=(float s)
{
	this->X /= s;
	this->Y /= s;
	this->Z /= s;
	this->W /= s;
	return *this;
}
#pragma warning(pop)

Point4 Point4::operator/(float s) const
{
	return Point4(
		int(this->X / s),
		int(this->Y / s),
		int(this->Z / s),
		int(this->W / s)
	);
}

Engine3DRadSpace::Math::Point4::operator Engine3DRadSpace::Math::Vector4() const
{
	return Vector4(
		float(X),
		float(Y),
		float(Z),
		float(W)
	);
}

Point4 operator*(float s, const Point4& p)
{
	return Point4(
		int(s * p.X),
		int(s * p.Y),
		int(s * p.Z),
		int(s * p.W)
	);
}

Point4 operator/(float s, const Point4& p)
{
	return Point4(
		int(s / p.X),
		int(s / p.Y),
		int(s / p.Z),
		int(s / p.W)
	);
}