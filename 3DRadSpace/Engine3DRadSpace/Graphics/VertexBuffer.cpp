#include "VertexBuffer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Logging;

void VertexBuffer::_debugInfo()
{
#ifdef _DEBUG
#ifdef USING_DX11
	const char bufferName[] = "VertexBuffer::_buffer";
	_buffer->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(bufferName) - 1, bufferName);
#endif
#endif
}

D3D11_USAGE VertexBuffer::_to_d3d11_usage(BufferUsage usage)
{
	switch (usage)
	{
	case BufferUsage::ReadWriteGPU: return D3D11_USAGE_DEFAULT;
	case BufferUsage::ReadOnlyGPU: return D3D11_USAGE_IMMUTABLE;
	case BufferUsage::ReadOnlyGPU_WriteOnlyCPU: return D3D11_USAGE_DYNAMIC;
	case BufferUsage::Staging: return D3D11_USAGE_STAGING;
	default: return D3D11_USAGE_DEFAULT;
	}
}

UINT Engine3DRadSpace::Graphics::VertexBuffer::d3d11_cpu_usage(BufferUsage usage)
{
	switch (usage)
	{
	case BufferUsage::ReadOnlyGPU_WriteOnlyCPU: return D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	case BufferUsage::Staging: return D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	default: return 0;
	}
}

VertexBuffer::VertexBuffer(
	_In_ GraphicsDevice* device,
	_In_reads_bytes_opt_(p_structSize * numVertices) const void* data,
	size_t p_structSize,
	size_t numVertices,
	BufferUsage usage
):
	_device(device),
	_numVerts(numVertices),
	_structSize(p_structSize)
{
#ifdef USING_DX11
	D3D11_BUFFER_DESC vertexBuffDesc{};
	vertexBuffDesc.ByteWidth = UINT(_structSize * numVertices);
	vertexBuffDesc.Usage = _to_d3d11_usage(usage);
	vertexBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBuffDesc.StructureByteStride = UINT(_structSize);
	vertexBuffDesc.CPUAccessFlags = d3d11_cpu_usage(usage);

	D3D11_SUBRESOURCE_DATA resource{};
	resource.pSysMem = data;

	HRESULT r = device->_device->CreateBuffer(&vertexBuffDesc, data != nullptr ? &resource : nullptr, _buffer.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a vertex buffer!");
#endif
	_debugInfo();
}

void VertexBuffer::SetData(void *data, size_t size)
{
#ifdef USING_DX11
	D3D11_MAPPED_SUBRESOURCE res{};

	HRESULT r = _device->_context->Map(_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &res);
	if (FAILED(r)) throw Exception("Failed to write a vertex buffer!");

	memset(res.pData, 0, _numVerts * _structSize);
	memcpy_s(res.pData, _numVerts * _structSize, data, _numVerts * _structSize);
	
	_device->_context->Unmap(_buffer.Get(), 0);
#endif
}

size_t VertexBuffer::ReadData(void** data)
{
#ifdef USING_DX11
	D3D11_MAPPED_SUBRESOURCE res{};
	_device->_context->Map(_buffer.Get(), 0, D3D11_MAP_READ, 0, &res);

	*data = res.pData;
	return size_t(res.DepthPitch);
#endif
}

void Engine3DRadSpace::Graphics::VertexBuffer::EndRead()
{
#ifdef USING_DX11
	_device->_context->Unmap(_buffer.Get(), 0);
#endif
}

void VertexBuffer::Set()
{
#ifdef USING_DX11
	unsigned strides = (UINT)this->_structSize;
	unsigned offsets = 0;
	this->_device->_context->IASetVertexBuffers(0, 1, _buffer.GetAddressOf(), &strides, &offsets);
#endif // USING_DX11
}

void VertexBuffer::Draw(unsigned startIndex)
{
	Set();
#if USING_DX11
	_device->_context->Draw(UINT(_numVerts), UINT(startIndex));
#endif
}

size_t VertexBuffer::TotalSize() const noexcept
{
	return _numVerts * _structSize;
}
size_t VertexBuffer::StructSize() const noexcept
{
	return _structSize;
}
size_t VertexBuffer::NumVertices() const noexcept
{
	return _numVerts;
}

void VertexBuffer::SetDebugName(const std::string& name)
{
#ifdef _DEBUG
#ifdef USING_DX11
	_buffer->SetPrivateData(WKPDID_D3DDebugObjectName, name.length() - 1, name.c_str());
#endif
#endif
}
