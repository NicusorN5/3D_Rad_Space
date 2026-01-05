#include "GraphicsDevice.hpp"
#include "../Logging/Logging.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "RenderTarget.hpp"
#include "DepthStencilBuffer.hpp"
#include "..\Core\AssetUUIDReader.hpp"
#include "GraphicsCommandList.hpp"
#include "BlendState.hpp"
#include "ShaderCompiler.hpp"
#include "SamplerState.hpp"
#include "DeferredCommandList.hpp"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

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

GraphicsDevice::GraphicsDevice(void* nativeWindowHandle, size_t width, size_t height) :
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
	else
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> rtTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;

		//assign texture to main render target.
		
		r = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), static_cast<void**>(&rtTexture));
		if (FAILED(r)) throw Exception("Failed to get the back buffer texture!");

		//_backbufferRT->_texture->Release();

		//Create shader resource view for back buffer
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = -1;
		srvDesc.Texture2D.MostDetailedMip = 0;

		r = _device->CreateShaderResourceView(rtTexture.Get(), &srvDesc, &srv);
		if (FAILED(r)) throw Exception("Failed to create shader resource view for the back buffer!");

		//assign render target view
		r = _device->CreateRenderTargetView(rtTexture.Get(), nullptr, &rtv);
		if (FAILED(r)) throw Exception("Failed to create the main render target!");

		_backbufferRT.reset(
			new RenderTarget(this,
				std::move(rtTexture),
				std::move(srv),
				std::move(rtv)
			)
		);
		_backbufferRT->_retrieveSize();
	}

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

	_screenQuad = std::make_unique<VertexBuffer>(
		this,
		quad.data(),
		sizeof(VertexPointUV),
		static_cast<size_t>(quad.size()),
		BufferUsage::ReadOnlyGPU
	);
	_screenQuad->SetDebugName("GraphicsDevice::_screenQuad");

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
	_immediateContext = std::make_unique<GraphicsCommandList>(this);
	_compiler = std::make_unique<DirectX11::ShaderCompiler>(this);

	Color white[] =
	{
		Colors::White, Colors::White,
		Colors::White, Colors::White
	};

	_white2x2 = std::make_unique<Texture2D>(
		this,
		white,
		2,
		2
	);

	Logging::SetLastMessage("Created D3D11 backend");
}

std::string_view GraphicsDevice::BackendName() const noexcept
{
	return std::string_view("DirectX11");
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

std::unique_ptr<IGraphicsCommandList> GraphicsDevice::CreateCommandList()
{
	return std::make_unique<DeferredCommandList>(this);
}

IGraphicsCommandList* GraphicsDevice::ImmediateContext()
{
	return _immediateContext.get();
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState(
	bool alphaCoverage,
	bool indepedentBlend,
	std::array<RenderTargetBlendState, 8> renderTargetBlendStates
)
{
	return std::make_unique<BlendState>(this, alphaCoverage, indepedentBlend, renderTargetBlendStates);
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState_Opaque()
{
	return std::make_unique<BlendState>(std::move(BlendState::Opaque(this)));
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState_AlphaBlend()
{
	return std::make_unique<BlendState>(std::move(BlendState::AlphaBlend(this)));
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState_Additive()
{
	return std::make_unique<BlendState>(std::move(BlendState::Additive(this)));
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState_NonPremultiplied()
{
	return std::make_unique<BlendState>(std::move(BlendState::NonPremultiplied(this)));
}

std::unique_ptr<IDepthStencilBuffer> GraphicsDevice::CreateDepthStencilBuffer(
	size_t x,
	size_t y
)
{
	return std::make_unique<DepthStencilBuffer>(this, x, y);
}

std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState(
	bool EnableDepth,
	DepthWriteMask Mask,
	ComparisonFunction Function,
	bool EnableStencil,
	uint8_t ReadMask,
	uint8_t WriteMask,
	FaceOperation FrontFace,
	FaceOperation BackFace
)
{
	return std::make_unique<DepthStencilState>(
		this,
		EnableDepth,
		Mask,
		Function,
		EnableStencil,
		ReadMask,
		WriteMask,
		FrontFace,
		BackFace
	);
}

std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthDefault()
{
	return std::make_unique<DepthStencilState>(std::move(DepthStencilState::DepthDefault(this)));
}
std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthNone()
{
	return std::make_unique<DepthStencilState>(std::move(DepthStencilState::DepthNone(this)));
}
std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthRead()
{
	return std::make_unique<DepthStencilState>(std::move(DepthStencilState::DepthRead(this)));
}
std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthReverseZ()
{
	return std::make_unique<DepthStencilState>(std::move(DepthStencilState::DepthReverseZ(this)));
}
std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthReadReverseZ()
{
	return std::make_unique<DepthStencilState>(std::move(DepthStencilState::DepthReadReverseZ(this)));
}

IShaderCompiler* GraphicsDevice::ShaderCompiler()
{
	return _compiler.get();
}

ITexture2D* GraphicsDevice::WhiteBlank()
{
	return _white2x2.get();
}

std::unique_ptr<IIndexBuffer> GraphicsDevice::CreateIndexBuffer(std::span<unsigned> indices)
{
	return std::make_unique<IndexBuffer>(this, indices);
}

std::unique_ptr<IIndexBuffer> GraphicsDevice::CreateIndexBuffer(size_t numIndices, BufferUsage usage)
{
	return std::make_unique<IndexBuffer>(this, numIndices, usage);
}

std::unique_ptr<IRasterizerState> GraphicsDevice::GetRasterizerState()
{
	return std::make_unique<RasterizerState>(this);
}

std::unique_ptr<IRasterizerState> GraphicsDevice::CreateRasterizerState(
	RasterizerFillMode filling,
	RasterizerCullMode culling,
	bool switchFrontBack,
	int depthBias,
	float depthBiasClamp,
	float slopeScaleDepthBias,
	bool depthClip,
	bool scissor,
	bool multisample,
	bool aaLine
)
{
	return std::make_unique<RasterizerState>(
		this,
		filling,
		culling,
		switchFrontBack,
		depthBias,
		depthBiasClamp,
		slopeScaleDepthBias,
		depthClip,
		scissor,
		multisample,
		aaLine
	);
}

std::unique_ptr<IRasterizerState> GraphicsDevice::CreateRasterizerState_CullNone()
{
	return std::make_unique<RasterizerState>(std::move(RasterizerState::CullNone(this)));
}

std::unique_ptr<IRasterizerState> GraphicsDevice::CreateRasterizerState_CullClockwise()
{
	return std::make_unique<RasterizerState>(std::move(RasterizerState::CullClockwise(this)));
}

std::unique_ptr<IRasterizerState> GraphicsDevice::CreateRasterizerState_CullCounterClockwise()
{
	return std::make_unique<RasterizerState>(std::move(RasterizerState::CullCounterClockwise(this)));
}

std::unique_ptr<IRasterizerState> GraphicsDevice::CreateRasterizerState_Wireframe()
{
	return std::make_unique<RasterizerState>(std::move(RasterizerState::Wireframe(this)));
}

std::unique_ptr<IRenderTarget> GraphicsDevice::CreateRenderTarget(
	size_t x,
	size_t y,
	PixelFormat format
)
{
	return std::make_unique<RenderTarget>(this, x, y, format);
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState()
{
	return std::make_unique<SamplerState>(this);
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState(
	TextureFilter Filter,
	TextureAddressMode AddressU,
	TextureAddressMode AddressV,
	TextureAddressMode AddressW,
	float MipLODBias,
	unsigned MaxAnisotropy,
	ComparisonFunction ComparisionFunction,
	const Math::Color &BorderColor,
	float MinLOD,
	float MaxLOD
)
{
	return std::make_unique<SamplerState>(
		this,
		Filter,
		AddressU,
		AddressV,
		AddressW,
		MipLODBias,
		MaxAnisotropy,
		ComparisionFunction,
		BorderColor,
		MinLOD,
		MaxLOD
	);
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_LinearClamp()
{
	return std::make_unique<SamplerState>(std::move(SamplerState::LinearClamp(this)));
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_LinearWrap()
{
	return std::make_unique<SamplerState>(std::move(SamplerState::LinearWrap(this)));
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_PointClamp()
{
	return std::make_unique<SamplerState>(std::move(SamplerState::PointClamp(this)));
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_PointWrap()
{
	return std::make_unique<SamplerState>(std::move(SamplerState::PointWrap(this)));
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_AnisotropicClamp()
{
	return std::make_unique<SamplerState>(std::move(SamplerState::AnisotropicClamp(this)));
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_AnisotropicWrap()
{
	return std::make_unique<SamplerState>(std::move(SamplerState::AnisotropicWrap(this)));
}

std::unique_ptr<ITexture2D> GraphicsDevice::CreateTexture2D(const std::filesystem::path& path)
{
	return std::make_unique<Texture2D>(this, path);
}

std::unique_ptr<ITexture2D> GraphicsDevice::CreateTexture2D(
	void* data,
	size_t x,
	size_t y,
	PixelFormat format,
	BufferUsage usage
)
{
	return std::make_unique<Texture2D>(this, data, x, y, format, usage);
}

std::unique_ptr<IVertexBuffer> GraphicsDevice::CreateVertexBuffer(
	const void* data,
	size_t structSize,
	size_t numVertices,
	BufferUsage usage
)
{
	return std::make_unique<VertexBuffer>(this, data, structSize, numVertices, usage);
}

IVertexBuffer* GraphicsDevice::GetScreenQuad() const noexcept
{
	return _screenQuad.get();
}

void* GraphicsDevice::NativeHandle() const noexcept
{
	return _device.Get();
}