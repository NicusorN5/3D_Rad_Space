#pragma once
#include "IGraphicsDevice.hpp"
#include "IGraphicsDevice.h"
#include "IDepthStencilBuffer.hpp"
#include "IDepthStencilState.hpp"
#include "IGraphicsCommandList.hpp"
#include "ITexture2D.hpp"
#include "IVertexBuffer.hpp"
#include "IBlendState.hpp"
#include "IRasterizerState.hpp"
#include "IIndexBuffer.hpp"
#include "ISamplerState.hpp"
#include "IRenderTarget.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

E3DRSP_IRasterizerState E3DRSP_IGraphicsDevice_GetRasterizerState(E3DRSP_IGraphicsDevice device)
{
	auto rasterizerState = reinterpret_cast<IGraphicsDevice*>(device)->GetRasterizerState();
	return rasterizerState.release();
}

const char* E3DRSP_IGraphicsDevice_GetBackendName(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->BackendName().c_str();
}

E3DRSP_Point E3DRSP_IGraphicsDevice_Resolution(E3DRSP_IGraphicsDevice device)
{
	auto res = reinterpret_cast<IGraphicsDevice*>(device)->Resolution();
	return E3DRSP_Point{ res.X, res.Y };
}

E3DRSP_IRenderTarget E3DRSP_IGraphicsDevice_GetBackBuffer(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->GetBackBuffer();
}

E3DRSP_ITexture2D E3DRSP_IGraphicsDevice_GetBackBufferTexture(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->GetBackBufferTexture();
}

E3DRSP_IDepthStencilBuffer E3DRSP_IGraphicsDevice_GetDepthBuffer(E3DRSP_IGraphicsDevice device)
{
	return &reinterpret_cast<IGraphicsDevice*>(device)->GetDepthBuffer();
}

E3DRSP_IBlendState E3DRSP_IGraphicsDevice_CreateBlendState(
	E3DRSP_IGraphicsDevice device,
	bool alphaCoverage,
	bool indepedentBlend,
	E3DRSP_RenderTargetBlendState renderTargetBlendStates[8]
)
{
	std::array<RenderTargetBlendState, 8> rtbStates;
	for (size_t i = 0; i < 8; i++)
	{
		rtbStates[i] = *reinterpret_cast<RenderTargetBlendState*>(&renderTargetBlendStates[i]);
	}

	return reinterpret_cast<IGraphicsDevice*>(device)->CreateBlendState(
		alphaCoverage,
		indepedentBlend,
		rtbStates
	).release();
}

E3DRSP_IBlendState E3DRSP_IGraphicsDevice_CreateBlendState_Opaque(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateBlendState_Opaque().release();
}

E3DRSP_IBlendState E3DRSP_IGraphicsDevice_CreateBlendState_AlphaBlend(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateBlendState_AlphaBlend().release();
}

E3DRSP_IBlendState E3DRSP_IGraphicsDevice_CreateBlendState_Additive(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateBlendState_Additive().release();
}

E3DRSP_IBlendState E3DRSP_IGraphicsDevice_CreateBlendState_NonPremultiplied(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateBlendState_NonPremultiplied().release();
}

E3DRSP_IDepthStencilBuffer E3DRSP_IGraphicsDevice_CreateDepthStencilBuffer(
	E3DRSP_IGraphicsDevice device,
	size_t x,
	size_t y
)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateDepthStencilBuffer(x, y).release();
}

E3DRSP_IDepthStencilState E3DRSP_IGraphicsDevice_CreateDepthStencilState(
	E3DRSP_IGraphicsDevice device,
	bool EnableDepth,
	E3DRSP_DepthWriteMask Mask,
	E3DRSP_ComparisonFunction Function,
	bool EnableStencil,
	uint8_t ReadMask,
	uint8_t WriteMask,
	E3DRSP_FaceOperation FrontFace,
	E3DRSP_FaceOperation BackFace
)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateDepthStencilState(
		EnableDepth,
		static_cast<DepthWriteMask>(Mask),
		static_cast<ComparisonFunction>(Function),
		EnableStencil,
		ReadMask,
		WriteMask,
		std::bit_cast<FaceOperation>(FrontFace),
		std::bit_cast<FaceOperation>(BackFace)
	).release();
}

E3DRSP_IDepthStencilState E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthDefault(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateDepthStencilState_DepthDefault().release();
}

E3DRSP_IDepthStencilState E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthNone(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateDepthStencilState_DepthNone().release();
}

E3DRSP_IDepthStencilState E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthRead(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateDepthStencilState_DepthRead().release();
}

E3DRSP_IDepthStencilState E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthReverseZ(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateDepthStencilState_DepthReverseZ().release();
}

E3DRSP_IDepthStencilState E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthReadReverseZ(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateDepthStencilState_DepthReadReverseZ().release();
}

E3DRSP_IShaderCompiler E3DRSP_IGraphicsDevice_ShaderCompiler(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->ShaderCompiler();
}

E3DRSP_ITexture2D E3DRSP_IGraphicsDevice_WhiteBlank(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->WhiteBlank();
}

E3DRSP_IVertexBuffer E3DRSP_IGraphicsDevice_GetScreenQuad(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->GetScreenQuad();
}

E3DRSP_IIndexBuffer E3DRSP_IGraphicsDevice_CreateIndexBuffer(
	E3DRSP_IGraphicsDevice device,
	unsigned* indices,
	size_t numIndices
)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateIndexBuffer(std::span<unsigned>(indices, numIndices)).release();
}

E3DRSP_IIndexBuffer E3DRSP_IGraphicsDevice_CreateIndexBuffer2(E3DRSP_IGraphicsDevice device, size_t numIndices, BufferUsage usage)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateIndexBuffer(numIndices, usage).release();
}

E3DRSP_IRasterizerState E3DRSP_IGraphicsDevice_CreateRasterizerState(
	E3DRSP_IGraphicsDevice device,
	E3DRSP_RasterizerFillMode filling,
	E3DRSP_RasterizerCullMode culling,
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
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateRasterizerState(
		static_cast<RasterizerFillMode>(filling),
		static_cast<RasterizerCullMode>(culling),
		switchFrontBack,
		depthBias,
		depthBiasClamp,
		slopeScaleDepthBias,
		depthClip,
		scissor,
		multisample,
		aaLine
	).release();
}

E3DRSP_IRasterizerState E3DRSP_IGraphicsDevice_CreateRasterizerState_CullNone(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateRasterizerState_CullNone().release();
}

E3DRSP_IRasterizerState E3DRSP_IGraphicsDevice_CreateRasterizerState_CullClockwise(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateRasterizerState_CullClockwise().release();
}

E3DRSP_IRasterizerState E3DRSP_IGraphicsDevice_CreateRasterizerState_CullCounterClockwise(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateRasterizerState_CullCounterClockwise().release();
}

E3DRSP_IRasterizerState E3DRSP_IGraphicsDevice_CreateRasterizerState_Wireframe(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateRasterizerState_Wireframe().release();
}

E3DRSP_IRenderTarget E3DRSP_IGraphicsDevice_CreateRenderTarget(
	E3DRSP_IGraphicsDevice device,
	size_t x,
	size_t y,
	PixelFormat format
)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateRenderTarget(x, y, format).release();
}

E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateSamplerState().release();
}

E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState2(
	E3DRSP_IGraphicsDevice device,
	E3DRSP_TextureFilter filter,
	E3DRSP_TextureAddressMode addressU,
	E3DRSP_TextureAddressMode addressV,
	E3DRSP_TextureAddressMode addressW,
	float mipLODBias,
	unsigned maxAnisotropy,
	E3DRSP_ComparisonFunction comparisonFunc,
	E3DRSP_Color borderColor,
	float minLOD,
	float maxLOD
)
{
	TextureFilter natFilter = static_cast<TextureFilter>(filter);
	TextureAddressMode natAddressU = static_cast<TextureAddressMode>(addressU);
	TextureAddressMode natAddressV = static_cast<TextureAddressMode>(addressV);
	TextureAddressMode natAddressW = static_cast<TextureAddressMode>(addressW);
	ComparisonFunction natComparisonFunc = static_cast<ComparisonFunction>(comparisonFunc);
	Math::Color natBorderColor = Math::Color{ borderColor.R, borderColor.G, borderColor.B, borderColor.A };

	return reinterpret_cast<IGraphicsDevice*>(device)->CreateSamplerState(
		natFilter,
		natAddressU,
		natAddressV,
		natAddressW,
		mipLODBias,
		maxAnisotropy,
		natComparisonFunc,
		natBorderColor,
		minLOD,
		maxLOD
	).release();
}

E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState_LinearClamp(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateSamplerState_LinearClamp().release();
}

E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState_LinearWrap(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateSamplerState_LinearWrap().release();
}

E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_reateSamplerState_PointClamp(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateSamplerState_PointClamp().release();
}

E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState_PointWrap(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateSamplerState_PointWrap().release();
}

E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState_AnisotropicClamp(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateSamplerState_AnisotropicClamp().release();
}

E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState_AnisotropicWrap(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateSamplerState_AnisotropicWrap().release();
}

E3DRSP_ITexture2D E3DRSP_IGraphicsDevice_CreateTexture2D(
	E3DRSP_IGraphicsDevice device,
	void* data,
	size_t x,
	size_t y,
	E3DRSP_PixelFormat format,
	E3DRSP_BufferUsage usage
)
{
	PixelFormat natFormat = static_cast<PixelFormat>(format);
	BufferUsage natUsage = static_cast<BufferUsage>(usage);

	return reinterpret_cast<IGraphicsDevice*>(device)->CreateTexture2D(
		data,
		x,
		y,
		natFormat,
		natUsage
	).release();
}

E3DRSP_ITexture2D E3DRSP_IGraphicsDevice_CreateTexture2DFromFile(E3DRSP_IGraphicsDevice device, const char* path)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateTexture2D(std::filesystem::path(path)).release();
}

E3DRSP_IVertexBuffer E3DRSP_IGraphicsDevice_CreateVertexBuffer(
	E3DRSP_IGraphicsDevice device,
	const void* data,
	size_t structSize,
	size_t numVertices,
	BufferUsage usage
)
{
	BufferUsage natUsage = static_cast<BufferUsage>(usage);
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateVertexBuffer(
		data,
		structSize,
		numVertices,
		natUsage
	).release();
}

E3DRSP_IGraphicsCommandList E3DRSP_IGraphicsDevice_CreateCommandList(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->CreateCommandList().release();
}

E3DRSP_IGraphicsCommandList E3DRSP_IGraphicsDevice_ImmediateContext(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->ImmediateContext();
}

void* E3DRSP_IGraphicsDevice_NativeHandle(E3DRSP_IGraphicsDevice device)
{
	return reinterpret_cast<IGraphicsDevice*>(device)->NativeHandle();
}

void E3DRSP_IGraphicsDevice_Destroy(E3DRSP_IGraphicsDevice device)
{
	delete reinterpret_cast<IGraphicsDevice*>(device);
}