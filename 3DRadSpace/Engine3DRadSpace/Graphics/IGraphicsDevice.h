#pragma once
#include "../Math/Point.h"
#include "../Math/Color.h"
#include "Viewport.h"
#include "VertexTopology.h"
#include "PixelFormat.h"
#include "BufferUsage.h"
#include "RenderTargetBlendState.h"
#include "DepthWriteMask.h"
#include "ComparisonFunction.h"
#include "FaceOperation.h"
#include "VertexDeclarations.h"
#include "../Core/IService.h"
#include "TextureFilter.h"
#include "TextureAddressMode.h"
#include "RasterizerFillMode.h"
#include "RasterizerCullMode.h"

typedef void* E3DRSP_IGraphicsDevice;
typedef void* E3DRSP_ITexture1D;
typedef void* E3DRSP_ITexture2D;
typedef void* E3DRSP_IRenderTarget;
typedef void* E3DRSP_IDepthStencilBuffer;
typedef void* E3DRSP_IVertexBuffer;
typedef void* E3DRSP_IIndexBuffer;
typedef void* E3DRSP_IShader;
typedef void* E3DRSP_IRasterizerState;
typedef void* E3DRSP_IDepthStencilState;
typedef void* E3DRSP_IBlendState;
typedef void* E3DRSP_ISamplerState;
typedef void* E3DRSP_IShaderCompiler;
typedef void* E3DRSP_IGraphicsCommandList;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT const char* E3DRSP_IGraphicsDevice_BackendName(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IRasterizerState E3DRSP_IGraphicsDevice_GetRasterizerState(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_Point E3DRSP_IGraphicsDevice_Resolution(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IRenderTarget E3DRSP_IGraphicsDevice_GetBackBuffer(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_ITexture2D E3DRSP_IGraphicsDevice_GetBackBufferTexture(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IDepthStencilBuffer E3DRSP_IGraphicsDevice_GetDepthBuffer(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IBlendState E3DRSP_IGraphicsDevice_CreateBlendState(
		E3DRSP_IGraphicsDevice device,
		bool alphaCoverage, 
		bool indepedentBlend,
		E3DRSP_RenderTargetBlendState renderTargetBlendStates[8]
	);
	
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IBlendState E3DRSP_IGraphicsDevice_CreateBlendState_Opaque(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IBlendState E3DRSP_IGraphicsDevice_CreateBlendState_AlphaBlend(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IBlendState E3DRSP_IGraphicsDevice_CreateBlendState_Additive(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IBlendState E3DRSP_IGraphicsDevice_CreateBlendState_NonPremultiplied(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IDepthStencilBuffer E3DRSP_IGraphicsDevice_CreateDepthStencilBuffer(
		E3DRSP_IGraphicsDevice device,
		size_t x,
		size_t y
	);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IDepthStencilState E3DRSP_IGraphicsDevice_CreateDepthStencilState(
		E3DRSP_IGraphicsDevice device,
		bool EnableDepth, 
		E3DRSP_DepthWriteMask Mask, 
		E3DRSP_ComparisonFunction Function,
		bool EnableStencil,
		uint8_t ReadMask,
		uint8_t WriteMask,
		E3DRSP_FaceOperation FrontFace,
		E3DRSP_FaceOperation BackFace
	);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IDepthStencilState E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthDefault(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IDepthStencilState E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthNone(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IDepthStencilState E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthRead(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IDepthStencilState E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthReverseZ(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IDepthStencilState E3DRSP_IGraphicsDevice_CreateDepthStencilState_DepthReadReverseZ(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IShaderCompiler E3DRSP_IGraphicsDevice_ShaderCompiler(E3DRSP_IGraphicsDevice device);
	///<summmary
	///Returns a 2x2 blank white texture.
	///</summary
	E3DRSP_GRAPHICS_EXPORT E3DRSP_ITexture2D E3DRSP_IGraphicsDevice_WhiteBlank(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IVertexBuffer E3DRSP_IGraphicsDevice_GetScreenQuad(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IIndexBuffer E3DRSP_IGraphicsDevice_CreateIndexBuffer(
		E3DRSP_IGraphicsDevice device,
		unsigned* indices,
		size_t numIndices
	);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IIndexBuffer E3DRSP_IGraphicsDevice_CreateIndexBuffer2(E3DRSP_IGraphicsDevice device, size_t numIndices, E3DRSP_BufferUsage usage);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IRasterizerState E3DRSP_IGraphicsDevice_CreateRasterizerState(
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
	);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IRasterizerState E3DRSP_IGraphicsDevice_CreateRasterizerState_CullNone(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IRasterizerState E3DRSP_IGraphicsDevice_CreateRasterizerState_CullClockwise(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IRasterizerState E3DRSP_IGraphicsDevice_CreateRasterizerState_CullCounterClockwise(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IRasterizerState E3DRSP_IGraphicsDevice_CreateRasterizerState_Wireframe(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IRenderTarget E3DRSP_IGraphicsDevice_CreateRenderTarget(
		E3DRSP_IGraphicsDevice device,
		size_t x,
		size_t y,
		E3DRSP_PixelFormat format
	);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState2(
		E3DRSP_IGraphicsDevice device,
		E3DRSP_TextureFilter filter,
		E3DRSP_TextureAddressMode addressU,
		E3DRSP_TextureAddressMode addressV,
		E3DRSP_TextureAddressMode addressW,
		float mipLODBias,
		unsigned maxAnisotropy,
		E3DRSP_ComparisonFunction comparisonFunc,
		const E3DRSP_Color* borderColor,
		float minLOD,
		float maxLOD
	);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState_LinearClamp(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState_LinearWrap(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_reateSamplerState_PointClamp(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState_PointWrap(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState_AnisotropicClamp(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_ISamplerState E3DRSP_IGraphicsDevice_CreateSamplerState_AnisotropicWrap(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_ITexture1D E3DRSP_IGraphicsDevice_CreateTexture1D(
		E3DRSP_IGraphicsDevice device,
		size_t numElements,
		E3DRSP_PixelFormat format
	);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_ITexture1D E3DRSP_IGraphicsDevice_CreateTexture1DCol(
		E3DRSP_IGraphicsDevice device,
		E3DRSP_Color* data,
		size_t numElements
	);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_ITexture2D E3DRSP_IGraphicsDevice_CreateTexture2D(
		E3DRSP_IGraphicsDevice device,
		void* data,
		size_t x,
		size_t y,
		E3DRSP_PixelFormat format,
		E3DRSP_BufferUsage usage
	);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_ITexture2D E3DRSP_IGraphicsDevice_CreateTexture2DFromFile(E3DRSP_IGraphicsDevice device, const char* path);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IVertexBuffer E3DRSP_IGraphicsDevice_CreateVertexBuffer(
		E3DRSP_IGraphicsDevice device,
		const void* data,
		size_t structSize,
		size_t numVertices,
		E3DRSP_BufferUsage usage
	);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IGraphicsCommandList E3DRSP_IGraphicsDevice_CreateCommandList(E3DRSP_IGraphicsDevice device);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IGraphicsCommandList E3DRSP_IGraphicsDevice_ImmediateContext(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT void* E3DRSP_IGraphicsDevice_NativeHandle(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IGraphicsDevice_Destroy(E3DRSP_IGraphicsDevice device);
#ifdef __cplusplus
}
#endif