#pragma once
#include "IGPUBuffer.h"

typedef void* E3DRSP_IVertexBuffer;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT size_t E3DRSP_IVertexBuffer_TotalSize(E3DRSP_IVertexBuffer vertexBuffer);
	E3DRSP_GRAPHICS_EXPORT size_t E3DRSP_IVertexBuffer_StructSize(E3DRSP_IVertexBuffer vertexBuffer);
	E3DRSP_GRAPHICS_EXPORT size_t E3DRSP_IVertexBuffer_NumVertices(E3DRSP_IVertexBuffer vertexBuffer);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IVertexBuffer E3DRSP_IVertexBuffer_CreateStaging(E3DRSP_IVertexBuffer vertexBuffer);
#ifdef __cplusplus
}
#endif