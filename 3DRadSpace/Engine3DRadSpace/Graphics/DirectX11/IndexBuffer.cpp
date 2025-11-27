#include "IndexBuffer.hpp"
#include "GraphicsDevice.hpp"
#include "../Logging/Logging.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;

void IndexBuffer::_debugInfo()
{
#ifdef _DEBUG
	const char indexBufferName[] = "IndexBuffer::_indexBuffer";
	_indexBuffer->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(indexBufferName) - 1, indexBufferName);
#endif
}

IndexBuffer::IndexBuffer(GraphicsDevice* device, Microsoft::WRL::ComPtr<ID3D11Buffer>&& buffer, unsigned numIndices) :
	_device(device),
	_indexBuffer(std::move(buffer)),
	_numIndices(numIndices)
{
}

IndexBuffer::IndexBuffer(GraphicsDevice* device, std::span<unsigned> indices):
	_device(device),
	_numIndices(unsigned(indices.size()))
{
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = UINT(indices.size() * sizeof(unsigned));
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.StructureByteStride = sizeof(unsigned);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = &indices[0];

	HRESULT r = device->_device->CreateBuffer(&desc, &data, &_indexBuffer);
	if (FAILED(r)) throw Exception("Failed to create a index buffer!");

	_debugInfo();
}

IndexBuffer::IndexBuffer(GraphicsDevice* device, size_t numIndices, BufferUsage usage) :
	_device(device),
	_numIndices(unsigned(numIndices))
{
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = UINT(numIndices * sizeof(unsigned));
	desc.StructureByteStride = sizeof(unsigned);
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	switch (usage)
	{
	case BufferUsage::ReadOnlyGPU:
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;
		break;
	case BufferUsage::ReadWriteGPU:
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;
		break;
	case BufferUsage::ReadOnlyGPU_WriteOnlyCPU:
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	default:
		throw Exception("Unsupported buffer usage for index buffer!");
	}
	HRESULT r = device->_device->CreateBuffer(&desc, nullptr, &_indexBuffer);
	if (FAILED(r)) throw Exception("Failed to create a index buffer!");

	_debugInfo();
}

void IndexBuffer::SetData(void* data, size_t buffSize)
{
	D3D11_MAPPED_SUBRESOURCE mappedBuff{};
	HRESULT r = _device->_context->Map(_indexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedBuff);
	if(FAILED(r)) throw Exception("Failed to map a index buffer!");

	memcpy_s(mappedBuff.pData, buffSize, data, buffSize);
	_device->_context->Unmap(_indexBuffer.Get(), 0);
}

size_t IndexBuffer::ReadData(void** data)
{
	D3D11_MAPPED_SUBRESOURCE res{};
	_device->_context->Map(_indexBuffer.Get(), 0, D3D11_MAP_READ, 0, &res);

	*data = res.pData;
	return res.DepthPitch;
}

void IndexBuffer::EndRead()
{
	_device->_context->Unmap(_indexBuffer.Get(), 0);
}

unsigned IndexBuffer::NumIndices() const noexcept
{
	return _numIndices;
}

void* IndexBuffer::GetHandle() const noexcept
{
	return static_cast<void*>(_indexBuffer.Get());
}

[[nodiscard]] std::unique_ptr<IIndexBuffer> IndexBuffer::CreateStaging()
{
	D3D11_BUFFER_DESC stagingIndexBufferDesc;
	_indexBuffer->GetDesc(&stagingIndexBufferDesc);
	stagingIndexBufferDesc.Usage = D3D11_USAGE_STAGING;
	stagingIndexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	stagingIndexBufferDesc.BindFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Buffer> stagingIndexBuffer;
	HRESULT r = _device->_device->CreateBuffer(&stagingIndexBufferDesc, nullptr, stagingIndexBuffer.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a staging index buffer!" + std::system_category().message(r));

	_device->_context->CopyResource(stagingIndexBuffer.Get(), _indexBuffer.Get());

	std::unique_ptr<IIndexBuffer> ptr;
	ptr.reset(new IndexBuffer(
		_device,
		std::move(stagingIndexBuffer),
		stagingIndexBufferDesc.ByteWidth / sizeof(unsigned)
	));
	return ptr;
}

void IndexBuffer::Set(unsigned offset)
{
	_device->_context->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);
}

IGraphicsDevice* IndexBuffer::GetGraphicsDevice() const noexcept
{
	return _device;
}