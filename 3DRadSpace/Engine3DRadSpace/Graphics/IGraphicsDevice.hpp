#pragma once
#include "../Math/Point.hpp"
#include "../Math/Color.hpp"
#include "Viewport.hpp"
#include "VertexTopology.hpp"

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

	class E3DRSP_GRAPHICS_EXPORT IGraphicsDevice
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

		virtual ~IGraphicsDevice() = default;
	};
}