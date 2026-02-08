#pragma once
#include "../Core/Libs.h"

typedef void* E3DRSP_ITexture1D;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT size_t E3DRSP_ITexture1D_Size(E3DRSP_ITexture1D texture);
	E3DRSP_GRAPHICS_EXPORT void* E3DRSP_ITexture1D_GetViewHandle(E3DRSP_ITexture1D texture);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_ITexture1D E3DRSP_ITexture1D_CreateStaging(E3DRSP_ITexture1D texture);
#ifdef __cplusplus
}
#endif // __cplusplus