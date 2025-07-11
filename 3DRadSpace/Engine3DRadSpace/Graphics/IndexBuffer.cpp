#include "IndexBuffer.hpp"
#include "GraphicsDevice.hpp"
#include "../Core/Logging.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Graphics;

void IndexBuffer::_debugInfo()
{
#ifdef _DEBUG
#ifdef USING_DX11
	const char indexBufferName[] = "IndexBuffer::_indexBuffer";
	_indexBuffer->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(indexBufferName) - 1, indexBufferName);
#endif
#endif
}

IndexBuffer::IndexBuffer(GraphicsDevice* device, Microsoft::WRL::ComPtr<ID3D11Buffer>&& buffer, unsigned numIndices) :
	_device(device),
	_indexBuffer(std::move(buffer)),
	_numIndices(numIndices)
{
}

IndexBuffer::IndexBuffer(GraphicsDevice* device,std::span<unsigned> indices):
	_device(device),
	_numIndices(unsigned(indices.size()))
{
#ifdef USING_DX11
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
#endif

	_debugInfo();
}

IndexBuffer::IndexBuffer(GraphicsDevice* device, unsigned* indices, size_t numindices):
	_device(device),
	_numIndices(unsigned(numindices))
{
#ifdef USING_DX11
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = UINT(numindices * sizeof(unsigned));
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.StructureByteStride = sizeof(unsigned);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = indices;

	HRESULT r = device->_device->CreateBuffer(&desc, indices != nullptr ? &data : nullptr, &_indexBuffer);
	if (FAILED(r)) throw Exception("Failed to create a index buffer!");
#endif
	_debugInfo();
}

void IndexBuffer::SetData(std::span<unsigned> newindices)
{
#ifdef USING_DX11
	D3D11_MAPPED_SUBRESOURCE mappedBuff{};
	HRESULT r = _device->_context->Map(_indexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedBuff);
	if (FAILED(r)) throw Exception("Failed to map a index buffer!");

	memset(mappedBuff.pData, 0, _numIndices * sizeof(unsigned));
	memcpy(mappedBuff.pData, &newindices[0], newindices.size_bytes());
	_device->_context->Unmap(_indexBuffer.Get(), 0);
#endif
}

size_t Engine3DRadSpace::Graphics::IndexBuffer::ReadData(void** data)
{
#ifdef USING_DX11
	D3D11_MAPPED_SUBRESOURCE res{};
	_device->_context->Map(_indexBuffer.Get(), 0, D3D11_MAP_READ, 0, &res);

	*data = res.pData;
	return res.DepthPitch;
#endif
}

void Engine3DRadSpace::Graphics::IndexBuffer::EndRead()
{
#ifdef USING_DX11
	_device->_context->Unmap(_indexBuffer.Get(), 0);
#endif
}

unsigned IndexBuffer::NumIndices() const noexcept
{
	return _numIndices;
}

void* IndexBuffer::GetHandle() const noexcept
{
#ifdef USING_DX11
	return static_cast<void*>(_indexBuffer.Get());
#endif
}

IndexBuffer IndexBuffer::CreateStaging()
{
#ifdef USING_DX11
	D3D11_BUFFER_DESC stagingIndexBufferDesc;
	_indexBuffer->GetDesc(&stagingIndexBufferDesc);
	stagingIndexBufferDesc.Usage = D3D11_USAGE_STAGING;
	stagingIndexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	stagingIndexBufferDesc.BindFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Buffer> stagingIndexBuffer;
	HRESULT r = _device->_device->CreateBuffer(&stagingIndexBufferDesc, nullptr, stagingIndexBuffer.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a staging index buffer!" + std::system_category().message(r));

	_device->_context->CopyResource(stagingIndexBuffer.Get(), _indexBuffer.Get());

	return IndexBuffer(_device, std::move(stagingIndexBuffer), stagingIndexBufferDesc.ByteWidth / sizeof(unsigned));
#endif
}

void IndexBuffer::Set(unsigned offset)
{
#ifdef USING_DX11
	_device->_context->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);
#endif
}
