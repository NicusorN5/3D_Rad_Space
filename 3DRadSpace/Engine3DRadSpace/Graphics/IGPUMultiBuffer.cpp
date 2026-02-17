#include "IGPUMultiBuffer.hpp"
#include "IGPUMultiBuffer.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

size_t E3DRSP_IGPUMultiBuffer_ReadData(E3DRSP_IGPUMultiBuffer buffer, size_t subResource, void** data)
{
	return static_cast<IGPUMultiBuffer*>(buffer)->ReadData(subResource, data);
}

void E3DRSP_IGPUMultiBuffer_SetData(E3DRSP_IGPUMultiBuffer buffer, size_t subResource, void* data, size_t buffSize)
{
	static_cast<IGPUMultiBuffer*>(buffer)->SetData(subResource, data, buffSize);
}

void E3DRSP_IGPUMultiBuffer_EndRead(E3DRSP_IGPUMultiBuffer buffer, size_t subResource)
{
	static_cast<IGPUMultiBuffer*>(buffer)->EndRead(subResource);
}