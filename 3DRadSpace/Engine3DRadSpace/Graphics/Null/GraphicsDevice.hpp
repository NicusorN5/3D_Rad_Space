#pragma once
#include "../IGraphicsDevice.hpp"
#include "../../Math/Color.hpp"
#include "../Viewport.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	/// <summary>
	/// Null GraphicsDevice implementation that doesn't make any GAPI calls.
	/// </summary>
	/// <remarks>
	/// A null graphics device can be used for a headless application, for servers, physics-only simulation, testing, et cetera...
	/// </remarks>
	class E3DRSP_GRAPHICS_NULL_EXPORT GraphicsDevice final : public IGraphicsDevice
	{
	public:
		GraphicsDevice() = delete;
		explicit GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);

		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;

		GraphicsDevice& operator=(const GraphicsDevice&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&&) = delete;

		void Clear(const Math::Color& clearColor = {0.0f, 0.0f, 0.0f, 1.0f}) override;
		void ClearRenderTarget(IRenderTarget* rt, const Math::Color& clearColor = {0.0f, 0.0f, 0.0f, 1.0f}) override;
		void ClearDepthBuffer(IDepthStencilBuffer* depth) override;

		void SetViewport() override;
		void SetViewport(const Viewport& viewport) override;

		void SetViewports(std::span<Viewport> viewports) override;
		Viewport GetViewport() override;

		void SetRenderTarget(IRenderTarget* renderTarget) override;
		
		void UnbindRenderTargetAndDepth() override;
		
		void UnbindDepthBuffer() override;
		
		void SetRenderTargetAndDepth(IRenderTarget* renderTarget, IDepthStencilBuffer* depthBuffer) override;
		
		void SetRenderTargetAndDisableDepth(IRenderTarget* renderTarget) override;

		void DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer) override;
		void DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer, unsigned numIndices) override;

		void SetShader(IShader* shader) override;

		void SetRasterizerState(const IRasterizerState* state) override;
		IRasterizerState* GetRasterizerState() override;

		void SetDepthStencilBuffer(IDepthStencilBuffer* depthBuffer) override;
		void SetDepthStencilState(IDepthStencilState* depthState, unsigned ref) override;

		void SetBlendState(IBlendState* blendState, const Math::Color& blendFactor = Math::Colors::Black, unsigned sampleMask = 0xFFFFFFFF) override;

		void SetTopology(VertexTopology topology) override;
		void DrawAuto() override;
		void Present() override;

		void SaveBackBufferToFile(const std::filesystem::path& path) override;

		bool EnableVSync;

		Math::Point Resolution() const noexcept override;

		void ResizeBackBuffer(const Math::Point& newResolution) override;
		void ToggleFullScreen() override;

		void SetScreenQuad() override;
		void DrawScreenQuad() override;

		IRenderTarget* GetBackBuffer() override;
		ITexture2D *GetBackBufferTexture() override;
		IDepthStencilBuffer& GetDepthBuffer() override;

		//Graphics::PixelFormat BackBufferFormat() const noexcept;

		~GraphicsDevice() override;
	};
}