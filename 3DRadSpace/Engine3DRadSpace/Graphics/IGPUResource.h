#pragma once
#include "../Core/Libs.h"

typedef void* E3DRSP_IGraphicsDevice;
typedef void* E3DRSP_IGPUResource;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IGraphicsDevice E3DRSP_IGPUResource_GetGraphicsDevice(E3DRSP_IGPUResource* resource);
	E3DRSP_GRAPHICS_EXPORT void* E3DRSP_IGPUResource_GetHandle(E3DRSP_IGPUResource* resource);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IGPUResource_Destroy(E3DRSP_IGPUResource* resource);
#ifdef __cplusplus
}
#endif