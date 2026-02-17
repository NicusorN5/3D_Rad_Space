#pragma once
#include "IGPUBuffer.h"
#include "../Math/UPoint3.h"

typedef void* E3DRSP_ITexture3D;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT E3DRSP_UPoint3 E3DRSP_ITexture3D_Size(E3DRSP_ITexture3D texture);
	E3DRSP_GRAPHICS_EXPORT unsigned E3DRSP_ITexture3D_Width(E3DRSP_ITexture3D texture);
	E3DRSP_GRAPHICS_EXPORT unsigned E3DRSP_ITexture3D_Height(E3DRSP_ITexture3D texture);
	E3DRSP_GRAPHICS_EXPORT unsigned E3DRSP_ITexture3D_Depth(E3DRSP_ITexture3D texture);
	E3DRSP_GRAPHICS_EXPORT void* E3DRSP_ITexture3D_GetViewHandle(E3DRSP_ITexture3D texture);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_ITexture3D E3DRSP_ITexture3D_CreateStaging(E3DRSP_ITexture3D texture);
#ifdef __cplusplus
}
#endif