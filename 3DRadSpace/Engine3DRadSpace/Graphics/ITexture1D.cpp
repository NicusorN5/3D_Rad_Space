#include "ITexture1D.hpp"
#include "ITexture1D.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

size_t E3DRSP_ITexture1D_Size(E3DRSP_ITexture1D texture)
{
	return static_cast<ITexture1D*>(texture)->Length();
}

void* E3DRSP_ITexture1D_GetViewHandle(E3DRSP_ITexture1D texture)
{
	return static_cast<ITexture1D*>(texture)->GetViewHandle();
}
E3DRSP_ITexture1D E3DRSP_ITexture1D_CreateStaging(E3DRSP_ITexture1D texture)
{
	return static_cast<ITexture1D*>(texture)->CreateStaging().release();
}