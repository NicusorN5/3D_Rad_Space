#include "GraphicsDevice.hpp"
#include "BlendState.hpp"
#include "RasterizerState.hpp"
#include "DepthStencilBuffer.hpp"
#include "DepthStencilState.hpp"
#include "ShaderCompiler.hpp"
#include "Texture2D.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "RenderTarget.hpp"
#include "SamplerState.hpp"
#include "GraphicsCommandList.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;
using namespace Engine3DRadSpace::Math;

GraphicsDevice::GraphicsDevice(void* nativeWindowHandle, size_t width, size_t height) :
	EnableVSync(false)
{
	(void)nativeWindowHandle;
	(void)width;
	(void)height;

	_depthStencilBuffer = std::make_unique<DepthStencilBuffer>(this);
	_compiler = std::make_unique<Null::ShaderCompiler>(this);
	_whiteBlankTexture = std::make_unique<Texture2D>(this, "");
	_context = std::make_unique<GraphicsCommandList>(this);
	_screenQuad = std::make_unique<VertexBuffer>(this, nullptr, 0, 0);
}

Math::Point GraphicsDevice::Resolution() const noexcept
{
	return Math::Point();
}

IRenderTarget* GraphicsDevice::GetBackBuffer()
{
	return nullptr;
}

ITexture2D* GraphicsDevice::GetBackBufferTexture()
{
	return nullptr;
}

std::unique_ptr<IRasterizerState> GraphicsDevice::GetRasterizerState()
{
	return std::make_unique<RasterizerState>(this);
}

IDepthStencilBuffer& GraphicsDevice::GetDepthBuffer()
{
	return *_depthStencilBuffer;
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState(
	bool alphaCoverage,
	bool indepedentBlend,
	std::array<RenderTargetBlendState, 8> renderTargetBlendStates
)
{
	return std::make_unique<BlendState>(this);
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState_Opaque()
{
	return std::make_unique<BlendState>(this);
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState_AlphaBlend()
{
	return std::make_unique<BlendState>(this);
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState_Additive()
{
	return std::make_unique<BlendState>(this);
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState_NonPremultiplied()
{
	 return std::make_unique<BlendState>(this);
}

std::unique_ptr<IDepthStencilBuffer> GraphicsDevice::CreateDepthStencilBuffer( size_t x, size_t y)
{
	return std::make_unique<DepthStencilBuffer>(this);
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
	return std::make_unique<DepthStencilState>(this);
}

std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthDefault()
{
	return std::make_unique<DepthStencilState>(this);
}
std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthNone()
{
	return std::make_unique<DepthStencilState>(this);
}
std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthRead()
{
	return std::make_unique<DepthStencilState>(this);
}
std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthReverseZ()
{
	return std::make_unique<DepthStencilState>(this);
}
std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthReadReverseZ()
{
	return std::make_unique<DepthStencilState>(this);
}

IShaderCompiler* GraphicsDevice::ShaderCompiler()
{
	return _compiler.get();
}

ITexture2D* GraphicsDevice::WhiteBlank()
{
	return _whiteBlankTexture.get();
}

std::unique_ptr<IIndexBuffer> GraphicsDevice::CreateIndexBuffer(std::span<unsigned> indices)
{
	return std::make_unique<IndexBuffer>(this, indices);
}

std::unique_ptr<IIndexBuffer> GraphicsDevice::CreateIndexBuffer(size_t numIndices, BufferUsage usage)
{
	return std::make_unique<IndexBuffer>(this, numIndices, usage);
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
	return std::make_unique<RasterizerState>(this);
}

std::unique_ptr<IRasterizerState> GraphicsDevice::CreateRasterizerState_CullClockwise()
{
	return std::make_unique<RasterizerState>(this);
}

std::unique_ptr<IRasterizerState> GraphicsDevice::CreateRasterizerState_CullCounterClockwise()
{
	return std::make_unique<RasterizerState>(this);
}

std::unique_ptr<IRasterizerState> GraphicsDevice::CreateRasterizerState_Wireframe()
{
	return std::make_unique<RasterizerState>(this);
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
	TextureFilter filter,
	TextureAddressMode addressU,
	TextureAddressMode addressV,
	TextureAddressMode addressW,
	float mipLODBias,
	unsigned maxAnisotropy,
	ComparisonFunction comparisonFunc,
	Math::Color borderColor,
	float minLOD,
	float maxLOD
)
{
	return std::make_unique<SamplerState>(
		this,
		filter,
		addressU,
		addressV,
		addressW,
		mipLODBias,
		maxAnisotropy,
		comparisonFunc,
		borderColor,
		minLOD,
		maxLOD
	);
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_LinearClamp()
{
	return std::make_unique<SamplerState>(this);
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_LinearWrap()
{
	return std::make_unique<SamplerState>(this);
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_PointClamp()
{
	return std::make_unique<SamplerState>(this);
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_PointWrap()
{
	return std::make_unique<SamplerState>(this);
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_AnisotropicClamp()
{
	return std::make_unique<SamplerState>(this);
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_AnisotropicWrap()
{
	return std::make_unique<SamplerState>(this);
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

std::unique_ptr<ITexture2D> GraphicsDevice::CreateTexture2D(const std::filesystem::path& path)
{
	return std::make_unique<Texture2D>(this, path);
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

std::unique_ptr<IGraphicsCommandList> GraphicsDevice::CreateCommandList()
{
	return std::make_unique<GraphicsCommandList>(this);
}

IGraphicsCommandList* GraphicsDevice::ImmediateContext()
{
	return _context.get();
}

IVertexBuffer* GraphicsDevice::GetScreenQuad() const noexcept
{
	return _screenQuad.get();
}

void* GraphicsDevice::NativeHandle() const noexcept
{
	return nullptr;
}

GraphicsDevice::~GraphicsDevice()
{
}