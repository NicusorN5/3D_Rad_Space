#include "GraphicsDevice.hpp"
#include "../Core/Logging.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "RenderTarget.hpp"
#include "DepthStencilBuffer.hpp"
#include "..\Core\AssetUUIDReader.hpp"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")

//#include <directxtk\ScreenGrab.h>
#include <wincodec.h>
#include <dxgidebug.h>
#include <dxgi.h>
#include <dxgi1_3.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;

GraphicsDevice::GraphicsDevice(void* nativeWindowHandle, unsigned width, unsigned height) :
	EnableVSync(true),
	_resolution(width, height)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	swapChainDesc.BufferDesc.RefreshRate = { 1,60 }; // 1/60
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc = { 1, 0 }; //count, quality
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT ;
	swapChainDesc.OutputWindow = static_cast<HWND>(nativeWindowHandle);
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

#if _DEBUG
	UINT flags = D3D11_CREATE_DEVICE_DEBUG;
#else
	UINT flags = 0;
#endif

	HRESULT r = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		flags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&_swapChain,
		&_device,
		nullptr,
		&_context
	);
	if (FAILED(r)) throw Exception("D3D11CreateDeviceAndSwapChain failed!");

	_backbufferRT = std::make_unique<RenderTarget>(std::move(RenderTarget(Internal::AssetUUIDReader{}))); //create a invalid render target, then correctly assign it.
	_backbufferRT->_device = this; //assign device handle

	//assign texture to main render target.
	r = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), static_cast<void**>(&_backbufferRT->_texture));
	if (FAILED(r)) throw Exception("Failed to get the back buffer texture!");

	//_backbufferRT->_texture->Release();
	_backbufferRT->_retrieveSize();

	//Create shader resource view for back buffer
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = -1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	r = _device->CreateShaderResourceView(_backbufferRT->_texture.Get(), &srvDesc, _backbufferRT->_resourceView.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create shader resource view for the back buffer!");

	//assign render target view
	r = _device->CreateRenderTargetView(_backbufferRT->_texture.Get(), nullptr, _backbufferRT->_renderTarget.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create the main render target!");

	_stencilBuffer = std::make_unique<DepthStencilBuffer>(this);
	_stencilState = std::make_unique<DepthStencilState>(this);
	_blendState = std::make_unique<BlendState>(this);

	_context->OMSetDepthStencilState(_stencilState->_state.Get(), 1);

	//create screen quad - used for post effects
	auto rr = RectangleF(0, 0, 1, 1);
	Vector2 a = rr.BottomLeft();
	a = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(a);

	Vector2 b = rr.TopLeft();
	b = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(b);

	Vector2 c = rr.TopRight();
	c = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(c);

	Vector2 d = rr.BottomRight();
	d = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(d);

	Vector2 uv_a = Vector2(0, 1);
	Vector2 uv_b = Vector2(0, 0);
	Vector2 uv_c = Vector2(1, 0);
	Vector2 uv_d = Vector2(1, 1);

	std::array<VertexPointUV, 6> quad =
	{
		VertexPointUV{a, uv_a},
		VertexPointUV{b, uv_b},
		VertexPointUV{c, uv_c},

		VertexPointUV{c, uv_c},
		VertexPointUV(d, uv_d),
		VertexPointUV{a, uv_a}
	};

	_screenQuad = std::make_unique<VertexBuffer>(std::span<VertexPointUV>(quad), BufferUsage::ReadOnlyGPU);
	//_screenQuad->SetDebugName("GraphicsDevice::_screenQuad");

#if _DEBUG
	const char deviceName[] = "GraphicsDevice::_device";
	_device->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(deviceName) - 1, deviceName);

	const char contextName[] = "GraphicsDevice::_context";
	_context->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(contextName) - 1, contextName);

	const char textureBackbufferName[] = "GraphicsDevice::_backbufferRT::_texture";
	_backbufferRT->_texture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureBackbufferName) - 1, textureBackbufferName);

	const char textureBackBufferViewName[] = "GraphicsDevice::_backBufferRT::_resourceView";
	_backbufferRT->_resourceView->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureBackBufferViewName) - 1, textureBackBufferViewName);

	const char renderTargetBackBufferName[] = "GraphicsDevice::_backBufferRT::_renderTarget";
	_backbufferRT->_renderTarget->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(renderTargetBackBufferName) - 1, renderTargetBackBufferName);
#endif
	Logging::SetLastMessage("Created D3D11 backend");
}

std::unique_ptr<IRasterizerState> GraphicsDevice::GetRasterizerState()
{
	auto c = ((RasterizerState*)nullptr)->GetCurrentRasterizerState(this);
	auto ptr = c.reset();

	std::unique_ptr<IRasterizerState> r;
	r.reset(ptr);

	return r;
}

Math::Point GraphicsDevice::Resolution() const noexcept
{
	return this->_resolution;
}

IRenderTarget* GraphicsDevice::GetBackBuffer()
{
	return _backbufferRT.get();
}

Graphics::ITexture2D* GraphicsDevice::GetBackBufferTexture()
{
	return dynamic_cast<Texture2D*>(this->_backbufferRT.get());
}

IDepthStencilBuffer& GraphicsDevice::GetDepthBuffer()
{
	return *this->_stencilBuffer;
}

GraphicsDevice::~GraphicsDevice()
{
	_context->ClearState();
//
//		UNCOMMENT THE COMMENT BLOCK BELOW IF THERE ARE DIRECTX OBJECTS LEAKING! 
//

/*
#if _DEBUG
	Microsoft::WRL::ComPtr<ID3D11Debug> debug;
	_device->QueryInterface<ID3D11Debug>(&debug);
	debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
#endif
*/
}