
#include "RenderTarget.hpp"
#include "../Logging/Exception.hpp"
#include "../Internal/AssetUUIDReader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

RenderTarget::RenderTarget(GraphicsDevice *device, PixelFormat format) :
	Texture2D(device, std::monostate{}, true, format)
{
#ifdef USING_DX11
	HRESULT r = device->_device->CreateRenderTargetView(_texture.Get(), nullptr, _renderTarget.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a render target!");
#endif
}

RenderTarget::RenderTarget(GraphicsDevice *device, unsigned x, unsigned y, PixelFormat format):
	Texture2D(device, x, y, true, format)
{
#ifdef USING_DX11
	HRESULT r = device->_device->CreateRenderTargetView(_texture.Get(), nullptr, _renderTarget.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a render target!");
#endif
}

RenderTarget::RenderTarget(GraphicsDevice* device, std::monostate cpy) :
	Texture2D(Internal::AssetUUIDReader{}) //create a invalid texture
{
	(void)cpy;

	_device = device;
#ifdef USING_DX11
	device->_context->OMGetRenderTargets(1, &_renderTarget, nullptr);

	ID3D11Resource* res;
	_renderTarget->GetResource(&res);

	ID3D11Texture2D *texture;
	HRESULT r = res->QueryInterface<ID3D11Texture2D>(&texture);
#endif
}

RenderTarget RenderTarget::GetCurrentRenderTarget(GraphicsDevice* device)
{
	return RenderTarget(device, std::monostate{});
}

void* RenderTarget::RenderTargetHandle() const noexcept
{
	return _renderTarget.Get();
}
