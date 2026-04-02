#include "Cone.h"
#include "../../../Objects/Impl/Cone.hpp"

using namespace Engine3DRadSpace::Objects;

E3DRSP_OCone E3DRSP_OCone_Create()
{
	return new Cone();
}

E3DRSP_Color E3DRSP_OCone_GetColor(E3DRSP_OCone cone)
{
	return std::bit_cast<E3DRSP_Color>(static_cast<Cone*>(cone)->Colour);
}

void E3DRSP_OCone_SetColor(E3DRSP_OCone cone, const E3DRSP_Color* color)
{
	static_cast<Cone*>(cone)->Colour = std::bit_cast<Color>(*color);
}

float E3DRSP_OCone_GetRadius(E3DRSP_OCone cone)
{
	return static_cast<Cone*>(cone)->Radius;
}

void E3DRSP_OCone_SetRadius(E3DRSP_OCone cone, float radius)
{
	static_cast<Cone*>(cone)->Radius = radius;
}

float E3DRSP_OCone_GetHeight(E3DRSP_OCone cone)
{
	return static_cast<Cone*>(cone)->Height;
}

void E3DRSP_OCone_SetHeight(E3DRSP_OCone cone, float height)
{
	static_cast<Cone*>(cone)->Height = height;
}

unsigned E3DRSP_OCone_GetResolution(E3DRSP_OCone cone)
{
	return static_cast<Cone*>(cone)->Resolution;
}

void E3DRSP_OCone_SetResolution(E3DRSP_OCone cone, unsigned resolution)
{
	static_cast<Cone*>(cone)->Resolution = resolution;
}