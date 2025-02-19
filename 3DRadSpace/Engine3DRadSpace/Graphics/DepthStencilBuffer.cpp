#include "DepthStencilBuffer.hpp"
#include "../Logging/Exception.hpp"
#include "Texture2D.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

void DepthStencilBuffer::_createDepthTexture()
{
#ifdef  USING_DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	desc.ArraySize = 1;
	desc.Width = _device->_resolution.X;
	desc.Height = _device->_resolution.Y;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> depthView;

	HRESULT r = _device->_device->CreateTexture2D(&desc, nullptr, depthTexture.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create the depth texture!");

	D3D11_DEPTH_STENCIL_VIEW_DESC viewDesc{};
	viewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT ;
	viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	r = _device->_device->CreateDepthStencilView(depthTexture.Get(), &viewDesc, &_depthView); //the & operator release the previous stencil view object
	if (FAILED(r)) throw Exception("Failed to create the depth stencil view!");

	D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc;
	sr_desc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	sr_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	sr_desc.Texture2D.MostDetailedMip = 0;
	sr_desc.Texture2D.MipLevels = -1;

	r = _device->_device->CreateShaderResourceView(depthTexture.Get(), &sr_desc, depthView.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create the depth stencil shader resource view!");

#ifdef _DEBUG
	const char depthTextureName[] = "DepthStencilBuffer::_depthTexture";
	depthTexture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(depthTextureName) - 1, depthTextureName);

	const char depthViewName[] = "DepthStencilBuffer::_depthView";
	_depthView->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(depthViewName) - 1, depthViewName);
#endif // _DEBUG

	_depthTexture.reset(new Texture2D(_device, std::move(depthTexture), std::move(depthView)));

#endif //  USING_DX11
}

DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice *device):
	_device(device)
{
	_createDepthTexture();
}

void* DepthStencilBuffer::GetViewHandle() const noexcept
{
	return static_cast<void*>(_depthView.Get());
}

void* DepthStencilBuffer::GetDepthTextureHandle() const noexcept
{
	return _depthTexture->TextureHandle();
}

Texture2D* DepthStencilBuffer::GetDepthTexture() const noexcept
{
	return this->_depthTexture.get();
}
