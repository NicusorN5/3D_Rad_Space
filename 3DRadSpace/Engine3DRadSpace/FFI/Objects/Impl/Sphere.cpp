#include "Sphere.h"
#include "../../../Objects/Impl/Sphere.hpp"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

E3DRSP_OSphere E3DRSP_OSphere_Create()
{
	return new Sphere();
}

E3DRSP_Color E3DRSP_OSphere_GetColor(E3DRSP_OSphere sphere)
{
	return std::bit_cast<E3DRSP_Color>(static_cast<Sphere*>(sphere)->Colour);
}

void E3DRSP_OSphere_SetColor(E3DRSP_OSphere sphere, const E3DRSP_Color* color)
{
	static_cast<Sphere*>(sphere)->Colour = std::bit_cast<Color>(*color);
}

float E3DRSP_OSphere_GetRadius(E3DRSP_OSphere sphere)
{
	return static_cast<Sphere*>(sphere)->Radius;
}

void E3DRSP_OSphere_SetRadius(E3DRSP_OSphere sphere, float radius)
{
	static_cast<Sphere*>(sphere)->Radius = radius;
}

unsigned E3DRSP_OSphere_GetResolution(E3DRSP_OSphere sphere)
{
	return static_cast<Sphere*>(sphere)->Resolution;
}

void E3DRSP_OSphere_SetResolution(E3DRSP_OSphere sphere, unsigned resolution)
{
	static_cast<Sphere*>(sphere)->Resolution = resolution;
}