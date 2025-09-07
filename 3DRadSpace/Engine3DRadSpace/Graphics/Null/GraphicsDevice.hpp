#pragma once
#include "../IGraphicsDevice.hpp"
#include "../../Math/Color.hpp"
#include "../Viewport.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class RenderTarget;
	class Texture2D;
	class DepthStencilBuffer;
	class DepthStencilState;
	class VertexBuffer;
	class IndexBuffer;
	class IShader;


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
		void ClearRenderTarget(RenderTarget* rt, const Math::Color& clearColor = {0.0f, 0.0f, 0.0f, 1.0f}) override;
		void ClearDepthBuffer(DepthStencilBuffer* depth) override;

		void SetViewport() override;
		void SetViewport(const Viewport& viewport) override;

		void SetViewports(std::span<Viewport> viewports) override;
		Viewport GetViewport() override;

		void SetRenderTarget(RenderTarget* renderTarget) override;
		
		void UnbindRenderTargetAndDepth() override;
		
		void UnbindDepthBuffer() override;
		
		void SetRenderTargetAndDepth(RenderTarget* renderTarget, DepthStencilBuffer* depthBuffer) override;
		
		void SetRenderTargetAndDisableDepth(RenderTarget* renderTarget) override;

		void DrawVertexBufferWithindices(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) override;
		void DrawVertexBufferWithindices(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, unsigned numIndices) override;

		void SetShader(IShader* shader) override;

		void SetRasterizerState(const RasterizerState* state) override;
		RasterizerState GetRasterizerState() override;

		void SetDepthStencilBuffer(DepthStencilBuffer* depthBuffer) override;
		void SetDepthStencilState(DepthStencilState* depthState, unsigned ref) override;

		void SetBlendState(BlendState* blendState, const Math::Color& blendFactor = Math::Colors::Black, unsigned sampleMask = 0xFFFFFFFF) override;

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

		RenderTarget* GetBackBuffer() override;
		Texture2D *GetBackBufferTexture() override;
		DepthStencilBuffer& GetDepthBuffer() override;

		//Graphics::PixelFormat BackBufferFormat() const noexcept;

		~GraphicsDevice() override;
	};
}