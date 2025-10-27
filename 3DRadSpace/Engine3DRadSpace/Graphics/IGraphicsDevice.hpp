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

	class IShaderCompiler;

	class E3DRSP_GRAPHICS_EXPORT IGraphicsDevice : public IService
	{
	protected:
		IGraphicsDevice() = default;
	public:
		virtual ITexture2D* CreateTexture(const std::filesystem::path& path);

		virtual void Clear(const Math::Color& clearColor) = 0;
		virtual void ClearRenderTarget(IRenderTarget* rt, const Math::Color& clearColor) = 0;
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

		virtual void SetBlendState(IBlendState* blendState, const Math::Color& blendFactor, unsigned sampleMask) = 0;

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

		virtual std::unique_ptr<IDepthStencilBuffer> CreateDepthStencilBuffer(
			size_t x,
			size_t y,
			PixelFormat format,
			BufferUsage usage
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

		virtual IShaderCompiler* ShaderCompiler() = 0;
		///<summmary>
		///Returns a 2x2 blank white texture.
		///</summary>
		virtual ITexture2D* WhiteBlank() = 0;

		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(std::span<unsigned> indices) = 0;
		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(size_t numIndices, BufferUsage usage) = 0;

		virtual std::unique_ptr<IRenderTarget> CreateRenderTarget(
			size_t x,
			size_t y,
			PixelFormat format
		) = 0;

		virtual std::unique_ptr<ITexture2D> CreateTexture2D(
			size_t x,
			size_t y,
			void* data,
			PixelFormat format,
			BufferUsage usage
		) = 0;

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