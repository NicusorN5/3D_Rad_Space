#include "IGPUResource.h"

typedef void* E3DRSP_IGPUMultiBuffer;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT size_t E3DRSP_IGPUMultiBuffer_ReadData(E3DRSP_IGPUMultiBuffer buffer, size_t subResource, void** data);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IGPUMultiBuffer_SetData(E3DRSP_IGPUMultiBuffer buffer, size_t subResource, void* data, size_t buffSize);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IGPUMultiBuffer_EndRead(E3DRSP_IGPUMultiBuffer buffer, size_t subResource);
#ifdef __cplusplus
}
#endif