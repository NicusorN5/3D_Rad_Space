#pragma once
#include "IGPUResource.h"

typedef void* E3DRSP_IGPUBuffer;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT size_t E3DRSP_IGPUBuffer_ReadData(E3DRSP_IGPUBuffer buffer, void** data);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IGPUBuffer_SetData(E3DRSP_IGPUBuffer buffer, void* data, size_t buffSize);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IGPUBuffer_EndRead(E3DRSP_IGPUBuffer buffer);
#ifdef __cplusplus
}
#endif