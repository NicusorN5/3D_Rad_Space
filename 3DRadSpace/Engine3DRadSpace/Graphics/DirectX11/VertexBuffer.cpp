#include "VertexBuffer.hpp"
#include "BufferUsage.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Logging;

void VertexBuffer::_debugInfo()
{
	const char bufferName[] = "VertexBuffer::_buffer";
	_buffer->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(bufferName) - 1, bufferName);
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
	D3D11_BUFFER_DESC vertexBuffDesc{};
	vertexBuffDesc.ByteWidth = UINT(_structSize * numVertices);
	vertexBuffDesc.Usage = BufferUsage_ToDirectX11(usage);
	vertexBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBuffDesc.CPUAccessFlags = BufferUsage_ToDX11CPUFlag(usage);
	vertexBuffDesc.StructureByteStride = UINT(_structSize);

	D3D11_SUBRESOURCE_DATA resource{};
	resource.pSysMem = data;

	HRESULT r = device->_device->CreateBuffer(&vertexBuffDesc, data != nullptr ? &resource : nullptr, _buffer.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a vertex buffer!");

	_debugInfo();
}


VertexBuffer::VertexBuffer(
	_In_ GraphicsDevice* device,
	Microsoft::WRL::ComPtr<ID3D11Buffer>&& vertexBuffer,
	size_t p_structSize,
	size_t numVertices
):
	_device(device),
	_buffer(std::move(vertexBuffer)),
	_numVerts(numVertices),
	_structSize(p_structSize)
{
}

void VertexBuffer::SetData(void *data, size_t size)
{
	D3D11_MAPPED_SUBRESOURCE res{};

	HRESULT r = _device->_context->Map(_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &res);
	if (FAILED(r)) throw Exception("Failed to write a vertex buffer!");

	memset(res.pData, 0, _numVerts * _structSize);
	memcpy_s(res.pData, _numVerts * _structSize, data, size);
	
	_device->_context->Unmap(_buffer.Get(), 0);
}

size_t VertexBuffer::ReadData(void** data)
{
	D3D11_MAPPED_SUBRESOURCE res{};
	_device->_context->Map(_buffer.Get(), 0, D3D11_MAP_READ, 0, &res);

	*data = res.pData;
	return size_t(res.DepthPitch);
}

void VertexBuffer::EndRead()
{
	_device->_context->Unmap(_buffer.Get(), 0);
}

void VertexBuffer::Set()
{
	unsigned strides = (UINT)this->_structSize;
	unsigned offsets = 0;
	this->_device->_context->IASetVertexBuffers(0, 1, _buffer.GetAddressOf(), &strides, &offsets);
}

void VertexBuffer::Draw(unsigned startIndex)
{
	Set();

	_device->_context->Draw(UINT(_numVerts), UINT(startIndex));
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
	_buffer->SetPrivateData(WKPDID_D3DDebugObjectName, name.length() - 1, name.c_str());
#endif
}

std::unique_ptr<IVertexBuffer> VertexBuffer::CreateStaging()
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> staging = nullptr;
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = UINT(_structSize * _numVerts);
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = UINT(_structSize);

	HRESULT r = _device->_device->CreateBuffer(&desc, nullptr, staging.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a staging buffer!" + std::system_category().message(r));
	
	_device->_context->CopyResource(staging.Get(), _buffer.Get());
	auto v = VertexBuffer(_device, std::move(staging), _structSize, _numVerts);
	return std::make_unique<VertexBuffer>(std::move(v));
}

void* VertexBuffer::GetHandle() const noexcept
{
	return _buffer.Get();
}

IGraphicsDevice* VertexBuffer::GetGraphicsDevice() const noexcept
{
	return _device;
}