#include "IndexBuffer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

IndexBuffer::IndexBuffer(GraphicsDevice* device, std::span<unsigned> indices)
{
	(void)device;
	(void)indices;
}

IndexBuffer::IndexBuffer(GraphicsDevice* device, unsigned* indices, size_t numIndices)
{
	(void)device;
	(void)indices;
	(void)numIndices;
}

void IndexBuffer::Set(unsigned index)
{
	(void)index;
}

void IndexBuffer::SetData(void* buffer, size_t bufferSize)
{
	(void)buffer;
	(void)bufferSize;
}

size_t IndexBuffer::ReadData(void** data)
{
	(void)data;
	return 0;
}

void IndexBuffer::EndRead()
{
}

unsigned IndexBuffer::NumIndices() const noexcept
{
	return 0;
}

void* IndexBuffer::GetHandle() const noexcept
{
	return nullptr;
}
