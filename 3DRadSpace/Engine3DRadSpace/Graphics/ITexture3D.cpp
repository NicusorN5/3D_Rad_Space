#include "ITexture3D.hpp"
#include "ITexture3D.h"

using namespace Engine3DRadSpace::Graphics;

E3DRSP_UPoint3 E3DRSP_ITexture3D_Size(E3DRSP_ITexture3D texture)
{
	auto s = static_cast<ITexture3D*>(texture)->Size();
	return {s.X, s.Y, s.Z};
}

unsigned E3DRSP_ITexture3D_Width(E3DRSP_ITexture3D texture)
{
	return static_cast<ITexture3D*>(texture)->Width();
}

unsigned E3DRSP_ITexture3D_Height(E3DRSP_ITexture3D texture)
{
	return static_cast<ITexture3D*>(texture)->Height();
}

unsigned E3DRSP_ITexture3D_Depth(E3DRSP_ITexture3D texture)
{
	return static_cast<ITexture3D*>(texture)->Depth();
}

void* E3DRSP_ITexture3D_GetViewHandle(E3DRSP_ITexture3D texture)
{
	return static_cast<ITexture3D*>(texture)->GetViewHandle();
}

E3DRSP_ITexture3D E3DRSP_ITexture3D_CreateStaging(E3DRSP_ITexture3D texture)
{
	return static_cast<ITexture3D*>(texture)->CreateStaging().release();
}