#pragma once

#include "../Core/Libs.hpp"
#include "Viewport.hpp"
#include "VertexDeclarations.hpp"
#include "VertexTopology.hpp"
#include "RasterizerState.hpp"
#include "DepthStencilState.hpp"
#include "DepthStencilBuffer.hpp"
#include "BlendState.hpp"
#include "IGraphicsDevice.hpp"

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
		class LineList;
		class LineStrip;
	}

	/// <summary>
	/// DirectX11 RHI (Rendering Hardware Interface)
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT GraphicsDevice : public IGraphicsDevice
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11Device> _device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context;
		Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
#endif
		std::unique_ptr<Graphics::RenderTarget> _backbufferRT;

		Math::Point _resolution;
		bool _fullscreen = false;

		std::unique_ptr<DepthStencilBuffer> _stencilBuffer;
		std::unique_ptr<DepthStencilState> _stencilState;
		std::unique_ptr<BlendState> _blendState;

		///Used for rendering post effects
		std::unique_ptr<Graphics::VertexBufferV<VertexPointUV>> _screenQuad;
	public:
		GraphicsDevice() = delete;
		explicit GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);

		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;

		GraphicsDevice& operator=(const GraphicsDevice&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&&) = delete;

		void Clear(const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f });
		void ClearRenderTarget(RenderTarget* rt, const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f });
		void ClearDepthBuffer(DepthStencilBuffer* depth);

		void SetViewport();
		void SetViewport(const Viewport& viewport);

		void SetViewports(std::span<Viewport> viewports);
		Viewport GetViewport();
		
		/// <summary>
		/// Sets the current render target. Depth buffer is set to the default depth buffer.
		/// </summary>
		/// <param name="remderTarget">Render target pointer reference. Using null will use the backbuffer.</param>
		void SetRenderTarget(RenderTarget* renderTarget);
		/// <summary>
		/// Unbinds the current render target and depth buffer. 
		/// </summary>
		/// <remarks>
		/// When called, there's no valid render surface that's assigned to the GPU. 
		/// </remarks>
		void UnbindRenderTargetAndDepth();
		/// <summary>
		/// Unbinds the current depth buffer.
		/// </summary>
		void UnbindDepthBuffer();
		/// <summary>
		/// Sets both render target and depth stencil buffer.
		/// </summary>
		/// <param name="renderTarget">Render surface to be drawn into. If null, it is set to the backbuffer.</param>
		/// <param name="depthBuffer">Depth stencil buffer. If null, will be set to the default non-null buffer.</param>
		void SetRenderTargetAndDepth(RenderTarget* renderTarget, DepthStencilBuffer* depthBuffer);
		/// <summary>
		/// Sets the render target, but unbinds the depth buffer.
		/// </summary>
		/// <param name="renderTarget">Render surface to be drawn into. If null, it is set to the backbuffer.</param>
		void SetRenderTargetAndDisableDepth(RenderTarget* renderTarget);

		/// <summary>
		/// Draws a vertex buffer into the selected render target.
		/// </summary>
		/// <param name="vertexBuffer">Vertex buffer.</param>
		/// <param name="startSlot">Index of the first buffer.</param>
		void DrawVertexBuffer(VertexBuffer* vertexBuffer, unsigned startSlot = 0);
		/// <summary>
		/// Draws a vertex buffer ordered by a index buffer into the selected render target.
		/// </summary>
		/// <param name="vertexBuffer">Vertex buffer.</param>
		/// <param name="indexBuffer">Index buffer.</param>
		void DrawVertexBufferWithindices(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer);
		void DrawVertexBufferWithindices(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, unsigned numIndices);

		/// <summary>
		/// Sets a shader for the graphics pipeline.
		/// </summary>
		/// <param name="shader">Either a vertex shader, fragment shader, geometry shader, etc...</param>
		void SetShader(IShader* shader);

		void SetRasterizerState(const RasterizerState* state);
		RasterizerState GetRasterizerState();

		void SetDepthStencilBuffer(DepthStencilBuffer* depthBuffer);
		void SetDepthStencilState(DepthStencilState* depthState, unsigned ref);

		void SetBlendState(BlendState* blendState, const Math::Color& blendFactor = Math::Colors::Black, unsigned sampleMask = 0xFFFFFFFF);

		/// <summary>
		/// Sets the topology used by the vertex buffer.
		/// </summary>
		/// <param name="topology"></param>
		void SetTopology(VertexTopology topology);
		void DrawAuto();
		/// <summary>
		/// Swaps the front and backbuffer, thus outputting the backbuffer to the screen.
		/// </summary>
		void Present();

		/// <summary>
		/// Writes the backbuffer to a file. 
		/// </summary>
		/// <param name="path">PNG format image path.</param>
		void SaveBackBufferToFile(const std::filesystem::path& path);

		bool EnableVSync;

		/// <summary>
		/// Returns the backbuffer width and height.
		/// </summary>
		/// <returns></returns>
		Math::Point Resolution() const noexcept;

		/// <summary>
		/// Resizes the back buffer, stencil buffer.
		/// </summary>
		/// <param name="newResolution">New resolution. Use 0,0 to match window size.</param>
		/// <remarks>
		/// Number of swap chain textures is preserved.
		/// Texture format will be same as the previous pixel format.
		/// </remarks>
		void ResizeBackBuffer(const Math::Point& newResolution);
		/// <summary>
		/// Switches the fullscreen state.
		/// </summary>
		void ToggleFullScreen();

		void SetScreenQuad();
		void DrawScreenQuad();

		RenderTarget* GetBackBuffer();
		Texture2D *GetBackBufferTexture();
		DepthStencilBuffer& GetDepthBuffer();

		//Graphics::PixelFormat BackBufferFormat() const noexcept;

		~GraphicsDevice();

		template<VertexDecl V> friend class VertexBufferV;

		friend class VertexBuffer;
		friend class IndexBuffer;
		friend class IShader;
		friend class Texture2D;
		friend class RenderTarget;
		friend class RasterizerState;
		friend class DepthStencilState;
		friend class SamplerState;
		friend class SpriteBatch;
		friend class DepthStencilBuffer;
		friend class BlendState;

		friend class IShader;
		friend class IVertexShader;
		friend class IHullShader;
		friend class IDomainShader;
		friend class IGeometryShader;
		friend class IFragmentShader;

		//TODO : Remove
		friend class Graphics::Primitives::LineList;
		friend class Graphics::Primitives::LineStrip;
	};
}
