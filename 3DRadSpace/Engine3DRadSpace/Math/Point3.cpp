#include "Point3.hpp"

using namespace Engine3DRadSpace::Math;

Point3 Point3::operator+=(const Point3& p)
{
	this->X += p.X;
	this->Y += p.Y;
	this->Z += p.Z;
	return *this;
}

Point3 Point3::operator+(const Point3& p) const
{
	return Point(
		this->X + p.X,
		this->Y + p.Y,
		this->Z + p.Z
	);
}

Point3 Point3::operator-=(const Point3& p)
{
	this->X -= p.X;
	this->Y -= p.Y;
	this->Z -= p.Z;
	return *this;
}

Point3 Point3::operator-(const Point3& p) const
{
	return Point(
		this->X - p.X,
		this->Y - p.Y,
		this->Z - p.Z
	);
}

Point3 Point3::operator-()
{
	this->X *= -1;
	this->Y *= -1;
	this->Z *= -1;
	return *this;
}

#pragma warning(push)
#pragma warning(disable : 4244)
Point3 Point3::operator*=(float s)
{
	this->X *= s;
	this->Y *= s;
	this->Z *= s;
	return *this;
}

Point3 Point3::operator*(float s) const
{
	return Point3(
		int(this->X * s ),
		int(this->Y * s),
		int(this->Z * s)
	);
}

Point3 Point3::operator/=(float s)
{
	this->X /= s;
	this->Y /= s;
	this->Z /= s;
	return *this;
}
#pragma warning(pop)

Point3 Point3::operator/(float s) const
{
	return Point3(
		int(this->X / s),
		int(this->Y / s),
		int(this->Z / s)
	);
}

Engine3DRadSpace::Math::Point3::operator Engine3DRadSpace::Math::Vector3() const
{
	return Vector3(
		float(X),
		float(Y),
		float(Z)
	);
}

Point3 operator*(float s, const Point3& p)
{
	return Point3(
		int(s * p.X),
		int(s * p.Y),
		int(x * p.Z)
	);
}

Point3 operator/(float s, const Point3& p)
{
	return Point3(
		int(s / p.X),
		int(s / p.Y),
		int(s / p.Z)
	);
}