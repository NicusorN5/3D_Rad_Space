#pragma once
#include "../Math/Point.hpp"
#include "../Math/Color.hpp"
#include "Viewport.hpp"
#include "VertexTopology.hpp"
#include "PixelFormat.hpp"
#include "BufferUsage.hpp"
#include "RenderTargetBlendState.hpp"
#include "DepthWriteMask.hpp"
#include "ComparisonFunction.hpp"
#include "FaceOperation.hpp"
#include "VertexDeclarations.hpp"
#include "../Core/IService.hpp"
#include "TextureFilter.hpp"
#include "TextureAddressMode.hpp"
#include "RasterizerFillMode.hpp"
#include "RasterizerCullMode.hpp"

namespace Engine3DRadSpace::Graphics
{
	class ITexture2D;
	class IRenderTarget;
	class IDepthStencilBuffer;
	class IVertexBuffer;
	class IIndexBuffer;
	class IShader;
	class IRasterizerState;
	class IDepthStencilState;
	class IBlendState;
	class ISamplerState;
	class IShaderCompiler;

	class E3DRSP_GRAPHICS_EXPORT IGraphicsDevice : public IService
	{
	protected:
		IGraphicsDevice() = default;
	public:
		virtual void Clear(const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f }) = 0;
		virtual void ClearRenderTarget(IRenderTarget* rt, const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f }) = 0;
		virtual void ClearDepthBuffer(IDepthStencilBuffer* depth) = 0;

		virtual void SetViewport() = 0;
		virtual void SetViewport(const Viewport& viewport) = 0;

		virtual void SetViewports(std::span<Viewport> viewports) = 0;
		virtual Viewport GetViewport() = 0;

		virtual void SetRenderTarget(IRenderTarget* renderTarget) = 0;

		virtual void UnbindRenderTargetAndDepth() = 0;

		virtual void UnbindDepthBuffer() = 0;

		virtual void SetRenderTargetAndDepth(IRenderTarget* renderTarget, IDepthStencilBuffer* depthBuffer) = 0;

		virtual void SetRenderTargetAndDisableDepth(IRenderTarget* renderTarget) = 0;

		virtual void DrawVertexBuffer(IVertexBuffer* vertexBuffer, unsigned startSlot = 0) = 0;
		virtual void DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer) = 0;
		virtual void DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer, unsigned numIndices) = 0;

		virtual void SetShader(IShader* shader) = 0;

		virtual void SetRasterizerState(const IRasterizerState* state) = 0;
		virtual IRasterizerState* GetRasterizerState() = 0;

		virtual void SetDepthStencilBuffer(IDepthStencilBuffer* depthBuffer) = 0;
		virtual void SetDepthStencilState(IDepthStencilState* depthState, unsigned ref) = 0;

		virtual void SetBlendState(IBlendState* blendState, const Math::Color& blendFactor = Math::Colors::Black, unsigned sampleMask = 0xFFFFFFFF) = 0;

		virtual void SetTopology(VertexTopology topology) = 0;
		virtual void DrawAuto() = 0;
		virtual void Present() = 0;

		virtual void SaveBackBufferToFile(const std::filesystem::path& path) = 0;

		virtual Math::Point Resolution() const noexcept = 0;

		virtual void ResizeBackBuffer(const Math::Point& newResolution) = 0;
		virtual void ToggleFullScreen() = 0;

		virtual void SetScreenQuad() = 0;
		virtual void DrawScreenQuad() = 0;

		virtual IRenderTarget* GetBackBuffer() = 0;
		virtual ITexture2D *GetBackBufferTexture() = 0;
		virtual IDepthStencilBuffer& GetDepthBuffer() = 0;

		virtual std::unique_ptr<IBlendState> CreateBlendState(
			bool alphaCoverage, 
			bool indepedentBlend,
			std::array<RenderTargetBlendState, 8> renderTargetBlendStates
		) = 0;

		virtual std::unique_ptr<IBlendState> CreateBlendState_Opaque() = 0;
		virtual std::unique_ptr<IBlendState> CreateBlendState_AlphaBlend() = 0;
		virtual std::unique_ptr<IBlendState> CreateBlendState_Additive() = 0;
		virtual std::unique_ptr<IBlendState> CreateBlendState_NonPremultiplied() = 0;

		virtual std::unique_ptr<IDepthStencilBuffer> CreateDepthStencilBuffer(
			size_t x,
			size_t y
		) = 0;

		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState(
			bool EnableDepth, 
			DepthWriteMask Mask, 
			ComparisonFunction Function,
			bool EnableStencil,
			uint8_t ReadMask,
			uint8_t WriteMask,
			FaceOperation FrontFace,
			FaceOperation BackFace
		) = 0;

		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthDefault() = 0;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthNone() = 0;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthRead() = 0;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthReverseZ() = 0;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthReadReverseZ() = 0;

		virtual IShaderCompiler* ShaderCompiler() = 0;
		///<summmary>
		///Returns a 2x2 blank white texture.
		///</summary>
		virtual ITexture2D* WhiteBlank() = 0;

		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(std::span<unsigned> indices) = 0;
		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(size_t numIndices, BufferUsage usage) = 0;

		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState(
			RasterizerFillMode filling = RasterizerFillMode::Solid,
			RasterizerCullMode culling = RasterizerCullMode::CullBack,
			bool switchFrontBack = false,
			int depthBias = 0,
			float depthBiasClamp = 0,
			float slopeScaleDepthBias = 0,
			bool depthClip = false,
			bool scissor = false,
			bool multisample = false,
			bool aaLine = false
		) = 0;

		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullNone() = 0;
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullClockwise() = 0;
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullCounterClockwise() = 0;
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_Wireframe() = 0;

		virtual std::unique_ptr<IRenderTarget> CreateRenderTarget(
			size_t x,
			size_t y,
			PixelFormat format
		) = 0;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState() = 0;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState(
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
		) = 0;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState_LinearClamp() = 0;
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_LinearWrap() = 0;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState_PointClamp() = 0;
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_PointWrap() = 0;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState_AnisotropicClamp() = 0;
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_AnisotropicWrap() = 0;

		virtual std::unique_ptr<ITexture2D> CreateTexture2D(
			size_t x,
			size_t y,
			void* data,
			PixelFormat format,
			BufferUsage usage
		) = 0;

		virtual std::unique_ptr<ITexture2D> CreateTexture2D(const std::filesystem::path& path) = 0;

		virtual std::unique_ptr<IVertexBuffer> CreateVertexBuffer(
			const void* data,
			size_t structSize,
			size_t numVertices,
			BufferUsage usage
		) = 0;

		template<VertexDecl V>
		std::unique_ptr<IVertexBuffer> CreateVertexBuffer(std::span<V> vertices, BufferUsage usage)
		{
			return CreateVertexBuffer(&vertices[0], sizeof(V), vertices.size(), usage);
		}

		template<VertexDecl V>
		std::unique_ptr<IVertexBuffer> CreateVertexBuffer(size_t numVertices, BufferUsage usage)
		{
			return CreateVertexBuffer(nullptr, sizeof(V), numVertices, usage);
		}

		virtual ~IGraphicsDevice() override = default;
	};
}