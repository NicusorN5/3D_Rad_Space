#include "IndexBuffer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

IndexBuffer::IndexBuffer(GraphicsDevice* device, std::span<unsigned> indices)
{
	(void)device;
	(void)indices;
}

IndexBuffer::IndexBuffer(GraphicsDevice* device, unsigned* indices, size_t numindices)
{
	(void)device;
	(void)indices;
	(void)numIndices;
}

void IndexBuffer::Set(unsigned index) override;
{
	(void)index;
}

void IndexBuffer::SetData(void* buffer, size_t bufferSize) override
{
	(void)buffer;
	(void)bufferSize;
}

void IndexBuffer::SetData(std::span<unsigned> newindices) override
{
	(void)newindices;
}

size_t IndexBuffer::ReadData(void** data) override
{
	(void)data;
	return 0;
}

void IndexBuffer::EndRead() override
{
}

unsigned IndexBuffer::NumIndices() const noexcept override
{
	return 0;
}

void* IndexBuffer::GetHandle() const noexcept override
{
	return nullptr;
}
