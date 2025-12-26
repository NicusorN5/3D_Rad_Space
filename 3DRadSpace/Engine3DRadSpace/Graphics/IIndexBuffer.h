#pragma once
#include "IGPUBuffer.h"

typedef void* E3DRSP_IIndexBuffer;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IIndexBuffer_Set(E3DRSP_IIndexBuffer indexBuffer, unsigned index);
	E3DRSP_GRAPHICS_EXPORT unsigned E3DRSP_IIndexBuffer_NumIndices(E3DRSP_IIndexBuffer indexBuffer);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IIndexBuffer E3DRSP_IIndexBuffer_CreateStaging(E3DRSP_IIndexBuffer indexBuffer);
#ifdef __cplusplus
}
#endif