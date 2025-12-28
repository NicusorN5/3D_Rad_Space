#include "IGPUBuffer.hpp"
#include "IGPUBuffer.h"

using namespace Engine3DRadSpace::Graphics;

size_t E3DRSP_IGPUBuffer_ReadData(E3DRSP_IGPUBuffer buffer, void** data)
{
	return reinterpret_cast<IGPUBuffer*>(buffer)->ReadData(data);
}

void E3DRSP_IGPUBuffer_SetData(E3DRSP_IGPUBuffer buffer, void* data, size_t buffSize)
{
	reinterpret_cast<IGPUBuffer*>(buffer)->SetData(data, buffSize);
}

void E3DRSP_IGPUBuffer_EndRead(E3DRSP_IGPUBuffer buffer)
{
	reinterpret_cast<IGPUBuffer*>(buffer)->EndRead();
}