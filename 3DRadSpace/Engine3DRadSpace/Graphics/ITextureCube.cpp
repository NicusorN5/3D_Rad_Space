#include "ITextureCube.hpp"
#include "ITextureCube.h"

using namespace Engine3DRadSpace::Graphics;

E3DRSP_UPoint E3DRSP_ITextureCube_Size(E3DRSP_ITextureCube texture)
{
	auto p = static_cast<ITextureCube*>(texture)->Size();
	return {p.X, p.Y};
}

unsigned E3DRSP_ITextureCube_Width(E3DRSP_ITextureCube texture)
{
	return static_cast<ITextureCube*>(texture)->Width();
}

unsigned E3DRSP_ITextureCube_Height(E3DRSP_ITextureCube texture)
{
	return static_cast<ITextureCube*>(texture)->Height();
}

void* E3DRSP_ITextureCube_GetViewHandle(E3DRSP_ITextureCube texture)
{
	return static_cast<ITextureCube*>(texture)->GetViewHandle();
}

E3DRSP_ITextureCube E3DRSP_ITextureCube_CreateStaging(E3DRSP_ITextureCube texture)
{
	return static_cast<E3DRSP_ITextureCube>(static_cast<ITextureCube*>(texture)->CreateStaging().release());
}