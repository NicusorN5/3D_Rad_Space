#pragma once
#include "../Math/UPoint.h"

typedef void* E3DRSP_ITextureCube;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT E3DRSP_UPoint E3DRSP_ITextureCube_Size(E3DRSP_ITextureCube texture);
	E3DRSP_GRAPHICS_EXPORT unsigned E3DRSP_ITextureCube_Width(E3DRSP_ITextureCube texture);
	E3DRSP_GRAPHICS_EXPORT unsigned E3DRSP_ITextureCube_Height(E3DRSP_ITextureCube texture);
	E3DRSP_GRAPHICS_EXPORT void* E3DRSP_ITextureCube_GetViewHandle(E3DRSP_ITextureCube texture);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_ITextureCube E3DRSP_ITextureCube_CreateStaging(E3DRSP_ITextureCube texture);
#ifdef __cplusplus
}
#endif