#pragma once
#include "../Core/Libs.h"

typedef void* E3DRSP_IRenderTarget;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT void* E3DRSP_IRenderTarget_RenderTargetHandle(E3DRSP_IRenderTarget renderTarget);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IRenderTarget_Destroy(E3DRSP_IRenderTarget renderTarget);
#ifdef __cplusplus
}
#endif