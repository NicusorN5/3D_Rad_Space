#include "Fog.h"
#include "../../../Objects/Impl/Fog.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

E3DRSP_Fog E3DRSP_Fog_Create()
{
	return new Fog();
}

float E3DRSP_Fog_GetFogBegin(E3DRSP_Fog fog)
{
	return static_cast<Fog*>(fog)->FogBegin;
}

void E3DRSP_Fog_SetFogBegin(E3DRSP_Fog fog, float fogBegin)
{
	static_cast<Fog*>(fog)->FogBegin = fogBegin;
}

float E3DRSP_Fog_GetFogEnd(E3DRSP_Fog fog)
{
	return static_cast<Fog*>(fog)->FogEnd;
}

void E3DRSP_Fog_SetFogEnd(E3DRSP_Fog fog, float fogEnd)
{
	static_cast<Fog*>(fog)->FogEnd = fogEnd;
}

E3DRSP_Color E3DRSP_Fog_GetFogColor(E3DRSP_Fog fog)
{
	return std::bit_cast<E3DRSP_Color>(static_cast<Fog*>(fog)->FogColor);
}

void E3DRSP_Fog_SetFogColor(E3DRSP_Fog fog, const E3DRSP_Color* fogCplor)
{
	static_cast<Fog*>(fog)->FogColor = std::bit_cast<Math::Color>(*fogCplor);
}