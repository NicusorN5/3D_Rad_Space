#include "Cylinder.h"
#include "../../../Objects/Impl/Cylinder.hpp"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

E3DRSP_OCylinder E3DRSP_OCylinder_Create()
{
	return new Cylinder();
}

E3DRSP_Color E3DRSP_OCylinder_GetColor(E3DRSP_OCylinder cylinder)
{
	return std::bit_cast<E3DRSP_Color>(static_cast<Cylinder*>(cylinder)->Colour);
}

void E3DRSP_OCylinder_SetColor(E3DRSP_OCylinder cylinder, const E3DRSP_Color* color)
{
	static_cast<Cylinder*>(cylinder)->Colour = std::bit_cast<Color>(*color);
}

float E3DRSP_OCylinder_GetRadius(E3DRSP_OCylinder cylinder)
{
	return static_cast<Cylinder*>(cylinder)->Radius;
}

void E3DRSP_OCylinder_SetRadius(E3DRSP_OCylinder cylinder, float radius)
{
	static_cast<Cylinder*>(cylinder)->Radius = radius;
}

float E3DRSP_OCylinder_GetHeight(E3DRSP_OCylinder cylinder)
{
	return static_cast<Cylinder*>(cylinder)->Height;
}

void E3DRSP_OCylinder_SetHeight(E3DRSP_OCylinder cylinder, float height)
{
	static_cast<Cylinder*>(cylinder)->Height = height;
}

unsigned E3DRSP_OCylinder_GetResolution(E3DRSP_OCylinder cylinder)
{
	return static_cast<Cylinder*>(cylinder)->Resolution;
}

void E3DRSP_OCylinder_SetResolution(E3DRSP_OCylinder cylinder, unsigned resolution)
{
	static_cast<Cylinder*>(cylinder)->Resolution = resolution;
}