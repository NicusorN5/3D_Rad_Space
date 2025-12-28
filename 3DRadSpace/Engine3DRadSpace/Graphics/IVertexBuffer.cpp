#include "IVertexBuffer.hpp"
#include "IVertexBuffer.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

size_t E3DRSP_IVertexBuffer_TotalSize(E3DRSP_IVertexBuffer vertexBuffer)
{
	return reinterpret_cast<IVertexBuffer*>(vertexBuffer)->TotalSize();
}

size_t E3DRSP_IVertexBuffer_StructSize(E3DRSP_IVertexBuffer vertexBuffer)
{
	return reinterpret_cast<IVertexBuffer*>(vertexBuffer)->StructSize();
}

size_t E3DRSP_IVertexBuffer_NumVertices(E3DRSP_IVertexBuffer vertexBuffer)
{
	return reinterpret_cast<IVertexBuffer*>(vertexBuffer)->NumVertices();
}

E3DRSP_IVertexBuffer E3DRSP_IVertexBuffer_CreateStaging(E3DRSP_IVertexBuffer vertexBuffer)
{
	auto staging = reinterpret_cast<IVertexBuffer*>(vertexBuffer)->CreateStaging();
	return reinterpret_cast<E3DRSP_IVertexBuffer>(staging.release());
}