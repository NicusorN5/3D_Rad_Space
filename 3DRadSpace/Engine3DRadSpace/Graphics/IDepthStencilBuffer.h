#pragma once
#include "IGPUResource.h"

typedef void* E3DRSP_ITexture2D;
typedef void* E3DRSP_IDepthStencilBuffer;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT void* E3DRSP_IDepthStencilBuffer_GetDepthTextureHandle(E3DRSP_IDepthStencilBuffer depthStencilBuffer);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_ITexture2D* E3DRSP_IDepthStencilBuffer_GetDepthTexture(E3DRSP_IDepthStencilBuffer depthStencilBuffer);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_ITexture2D* E3DRSP_IDepthStencilBuffer_CloneDepthTexture(E3DRSP_IDepthStencilBuffer depthStencilBuffer);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IDepthStencilBuffer_Destroy(E3DRSP_IDepthStencilBuffer depthStencilBuffer);
#ifdef __cplusplus
}
#endif