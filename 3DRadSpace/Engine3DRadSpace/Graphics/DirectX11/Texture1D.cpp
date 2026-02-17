#include "Texture1D.hpp"
#include "PixelFormat.hpp"
#include "../Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Math;

Texture1D::Texture1D(GraphicsDevice* device, size_t numElements, PixelFormat format) :
	_device(device),
	_size(numElements)
{
	D3D11_TEXTURE1D_DESC desc{};
	desc.Width = static_cast<UINT>(numElements);
	desc.ArraySize = 1;
	desc.MipLevels = 1;
	desc.Format = PixelFormat_ToDX11(format);
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT r = _device->_device->CreateTexture1D(&desc, nullptr, _texture.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to initialize a 2D texture!" + std::system_category().message(r));

	_createSRV();
	_setDebugInfo();
}

Texture1D::Texture1D(GraphicsDevice* device, std::span<Color> colors) :
	_device(device),
	_size(colors.size_bytes())
{
	D3D11_TEXTURE1D_DESC desc{};
	desc.Width = static_cast<UINT>(colors.size_bytes());
	desc.ArraySize = 1;
	desc.MipLevels = 1;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = colors.data();
	data.SysMemPitch = static_cast<UINT>(colors.size_bytes());
	data.SysMemSlicePitch = 0;

	HRESULT r = _device->_device->CreateTexture1D(&desc, &data, _texture.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to initialize a 2D texture!" + std::system_category().message(r));

	_createSRV();
	_setDebugInfo();
}

Texture1D::Texture1D(GraphicsDevice* device, D3D11_TEXTURE1D_DESC* desc, Microsoft::WRL::ComPtr<ID3D11Texture1D>&& texture) :
	_device(device),
	_texture(std::move(texture)),
	_shaderResourceView(nullptr),
	_format(PixelFormat_FromDX11(desc->Format)),
	_size(desc->Width)
{
}

void Texture1D::_setDebugInfo()
{
#ifdef _DEBUG
	const char textureName[] = "Texture1D::_texture";
	_texture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureName) - 1, textureName);

	const char resourceViewName[] = "Texture1D::_resourceView";
	_shaderResourceView->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(resourceViewName) - 1, resourceViewName);
#endif
}

void Texture1D::_createSRV()
{
	HRESULT r = _device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _shaderResourceView.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a shader resource view! " + std::system_category().message(r));
}

size_t Texture1D::Length() const noexcept
{
	return _size;
}

void* Texture1D::GetViewHandle() const noexcept
{
	return _shaderResourceView.Get();
}

std::unique_ptr<ITexture1D> Texture1D::CreateStaging()
{
	D3D11_TEXTURE1D_DESC desc{};
	_texture->GetDesc(&desc);

	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;

	Microsoft::WRL::ComPtr<ID3D11Texture1D> stagingTexture;
	HRESULT r = _device->_device->CreateTexture1D(&desc, nullptr, stagingTexture.GetAddressOf());

	if(FAILED(r)) throw Exception("Failed to create a staging texture! " + std::system_category().message(r));
	return std::make_unique<Texture1D>(Texture1D(_device, &desc, std::move(stagingTexture)));
}

size_t Texture1D::ReadData(size_t subResource, void** data)
{
	if(data == nullptr) return 0;

	D3D11_MAPPED_SUBRESOURCE mappedResource{};
	HRESULT r = _device->_context->Map(_texture.Get(), subResource, D3D11_MAP_READ, 0, &mappedResource);
	if(SUCCEEDED(r)) return mappedResource.RowPitch;
	else return 0;
}

void Texture1D::SetData(size_t subResource, void* data, size_t buffSize)
{
	if(data == nullptr) return;

	D3D11_MAPPED_SUBRESOURCE mappedResource{};
	HRESULT r = _device->_context->Map(_texture.Get(), subResource, D3D11_MAP_WRITE, 0, &mappedResource);
	if(FAILED(r)) throw Exception("Failed to map a texture!" + std::system_category().message(r));
	
	memcpy(mappedResource.pData, data, buffSize);
	_device->_context->Unmap(_texture.Get(), 0);
}

void Texture1D::EndRead(size_t subResource)
{
	_device->_context->Unmap(_texture.Get(), subResource);
}

void* Texture1D::GetHandle() const noexcept
{
	return _texture.Get();
}

IGraphicsDevice* Texture1D::GetGraphicsDevice() const noexcept
{
	return _device;
}