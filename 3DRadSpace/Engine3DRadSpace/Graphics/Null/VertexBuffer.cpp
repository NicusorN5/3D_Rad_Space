#include "VertexBuffer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

VertexBuffer::VertexBuffer(
	_In_ GraphicsDevice* device,
	_In_reads_bytes_opt_(p_structSize* numVertices) const void* data,
	size_t p_structSize,
	size_t numVertices,
	BufferUsage usage = BufferUsage::ReadOnlyGPU
)
{

}

void VertexBuffer::SetData(void* data, size_t dataSize)
{
	(void)data;
	(void)dataSize;
}

size_t VertexBuffer::ReadData(void** data)
{
	(void)data;
	return 0;
}

void VertexBuffer::EndRead()
{
}

void VertexBuffer::Set()
{
}
void VertexBuffer::Draw(unsigned startIndex = 0)
{
}

size_t VertexBuffer::TotalSize() const noexcept
{
	return 0;
}

size_t VertexBuffer::StructSize() const noexcept
{
	return 0;
}

size_t VertexBuffer::NumVertices() const noexcept
{
	return 0;
}

void VertexBuffer::SetDebugName(const std::string& name)
{
	(void)name;
}

void* VertexBuffer::GetHandle() const noexcept
{
	return nullptr;
}

IGraphicsDevice* VertexBuffer::GetGraphicsDevice() const noexcept
{
	return nullptr;
}

[[nodiscard]] std::unique_ptr<IVertexBuffer> CreateStaging()
{
	return std::unique_ptr<IVertexBuffer>(nullptr);
}