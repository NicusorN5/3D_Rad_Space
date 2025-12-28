#pragma once
#include "IGPUBuffer.h"
#include "../Math/Point.h"

typedef void* E3DRSP_ITexture2D;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT E3DRSP_Point E3DRSP_ITexture2D_Size(E3DRSP_ITexture2D texture);
	E3DRSP_GRAPHICS_EXPORT unsigned E3DRSP_ITexture2D_Width(E3DRSP_ITexture2D texture);
	E3DRSP_GRAPHICS_EXPORT unsigned E3DRSP_ITexture2D_Height(E3DRSP_ITexture2D texture);
	E3DRSP_GRAPHICS_EXPORT void* E3DRSP_ITexture2D_GetViewHandle(E3DRSP_ITexture2D texture);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_ITexture2D E3DRSP_ITexture2D_CreateStaging(E3DRSP_ITexture2D texture);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_ITexture2D_SaveToFile(E3DRSP_ITexture2D texture, const char* path);
#ifdef __cplusplus
}
#endif