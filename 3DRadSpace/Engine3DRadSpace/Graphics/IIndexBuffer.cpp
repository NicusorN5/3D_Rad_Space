#include "IIndexBuffer.hpp"
#include "IIndexBuffer.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

void E3DRSP_IIndexBuffer_Set(E3DRSP_IIndexBuffer indexBuffer, unsigned index)
{
	reinterpret_cast<IIndexBuffer*>(indexBuffer)->Set(index);
}

unsigned E3DRSP_IIndexBuffer_NumIndices(E3DRSP_IIndexBuffer indexBuffer)
{
	return reinterpret_cast<IIndexBuffer*>(indexBuffer)->NumIndices();
}

E3DRSP_IIndexBuffer E3DRSP_IIndexBuffer_CreateStaging(E3DRSP_IIndexBuffer indexBuffer)
{
	auto stagingBuffer = reinterpret_cast<IIndexBuffer*>(indexBuffer)->CreateStaging().release();
	return static_cast<E3DRSP_IIndexBuffer>(stagingBuffer);
}