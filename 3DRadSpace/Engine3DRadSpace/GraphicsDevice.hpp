#pragma once

#include "Libs.hpp"
#include "Viewport.hpp"
#include "Graphics/VertexDeclarations.hpp"
#include "Graphics/VertexTopology.hpp"
#include "Graphics/RasterizerState.hpp"
#include "Graphics/DepthStencilState.hpp"
#include "Graphics/DepthStencilBuffer.hpp"
#include "Graphics/BlendState.hpp"

namespace Engine3DRadSpace::Graphics
{
	template<VertexDecl V> class VertexBufferV;
	class VertexBuffer;
	class IndexBuffer;

	class IShader;
	class Texture2D;
	class RenderTarget;
	class DepthStencilBuffer;
	class DepthStencilState;
	class SpriteBatch;
	class SamplerState;
	class RenderTarget;
	class BlendState;

	class IShader;
	class IVertexShader;
	class IHullShader;
	class IDomainShader;
	class IGeometryShader;
	class IFragmentShader;

	namespace Primitives
	{
		class Lines;
	}
}

namespace Engine3DRadSpace
{
	/// <summary>
	/// DirectX11 RHI (Rendering Hardware Interface)
	/// </summary>
	class DLLEXPORT GraphicsDevice
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11Device> _device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context;
		Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
#endif
		std::unique_ptr<Graphics::RenderTarget> _backbufferRT;

		Math::Point _resolution;
		bool _fullscreen = false;

		std::unique_ptr<Graphics::DepthStencilBuffer> _stencilBuffer;
		std::unique_ptr<Graphics::DepthStencilState> _stencilState;
		std::unique_ptr<Graphics::BlendState> _blendState;

		///Used for rendering post effects
		std::unique_ptr<Graphics::VertexBufferV<Graphics::VertexPointUV>> _screenQuad;
	public:
		GraphicsDevice() = delete;
		explicit GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);

		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;

		GraphicsDevice& operator=(const GraphicsDevice&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&&) = delete;

		void Clear(const Color& clearColor = { 0.0f,0.0f,0.0f,1.0f });

		void SetViewport();
		void SetViewport(const Viewport& viewport);

		void SetViewports(std::span<Viewport> viewports);
		Viewport GetViewport();
		
		/// <summary>
		/// Sets the current render target.
		/// </summary>
		/// <param name="remderTarget">Render target pointer reference. Using null will use the backbuffer.</param>
		void SetRenderTarget(Graphics::RenderTarget* renderTarget);
		void SetRenderTargetAndDepth(Graphics::RenderTarget* renderTarget, Graphics::DepthStencilBuffer* depthBuffer);
		void SetRenderTargetAndDisableDepth(Graphics::RenderTarget* renderTarget);

		void DrawVertexBuffer(Graphics::VertexBuffer* vertexBuffer, unsigned startSlot = 0);
		void DrawVertexBufferWithindices(Graphics::VertexBuffer* vertexBuffer, Graphics::IndexBuffer* indexBuffer);
		void DrawVertexBufferWithindices(Graphics::VertexBuffer* vertexBuffer, Graphics::IndexBuffer* indexBuffer, unsigned numIndices);

		void SetShader(Graphics::IShader* shader);

		void SetRasterizerState(const Graphics::RasterizerState* state);

		void SetDepthStencilBuffer(Graphics::DepthStencilBuffer* depthBuffer);
		void SetDepthStencilState(Graphics::DepthStencilState* depthState, unsigned ref);

		void SetBlendState(Graphics::BlendState* blendState, const Color& blendFactor = Colors::Black, unsigned sampleMask = 0xFFFFFFFF);

		void SetTopology(Graphics::VertexTopology topology);
		void DrawAuto();
		void Present();

		void SaveBackBufferToFile(const std::filesystem::path& path);

		bool EnableVSync;

		Math::Point Resolution() const noexcept;

		void ResizeBackBuffer(const Math::Point& newResolution);
		void ToggleFullScreen();

		void SetScreenQuad();
		void DrawScreenQuad();

		Graphics::RenderTarget* GetBackBuffer();
		Graphics::Texture2D *GetBackBufferTexture();
		Graphics::DepthStencilBuffer& GetDepthBuffer();

		~GraphicsDevice();

		template<Graphics::VertexDecl V> friend class Graphics::VertexBufferV;

		friend class Graphics::VertexBuffer;
		friend class Graphics::IndexBuffer;
		friend class Graphics::IShader;
		friend class Graphics::Texture2D;
		friend class Graphics::RenderTarget;
		friend class Graphics::RasterizerState;
		friend class Graphics::DepthStencilState;
		friend class Graphics::SamplerState;
		friend class Graphics::SpriteBatch;
		friend class Graphics::DepthStencilBuffer;
		friend class Graphics::BlendState;

		friend class Graphics::IShader;
		friend class Graphics::IVertexShader;
		friend class Graphics::IHullShader;
		friend class Graphics::IDomainShader;
		friend class Graphics::IGeometryShader;
		friend class Graphics::IFragmentShader;

		//TODO : Remove
		friend class Graphics::Primitives::Lines;
	};
}
