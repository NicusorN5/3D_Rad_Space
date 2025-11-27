#include "IndexBuffer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

IndexBuffer::IndexBuffer(GraphicsDevice* device, std::span<unsigned> indices)
{
	(void)device;
	(void)indices;
}

IndexBuffer::IndexBuffer(GraphicsDevice* device, size_t numIndices, BufferUsage usage)
{
	(void)device;
	(void)numIndices;
	(void)usage;
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

std::unique_ptr<IIndexBuffer> IndexBuffer::CreateStaging()
{
	return std::make_unique<IndexBuffer>(nullptr, std::span<unsigned>());
}

IGraphicsDevice* IndexBuffer::GetGraphicsDevice() const noexcept
{
	return nullptr;
}