#pragma once

#include "../../Core/Libs.hpp"
#include "../Viewport.hpp"
#include "../VertexDeclarations.hpp"
#include "../VertexTopology.hpp"
#include "RasterizerState.hpp"
#include "DepthStencilState.hpp"
#include "DepthStencilBuffer.hpp"
#include "BlendState.hpp"
#include "../IGraphicsDevice.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	template<VertexDecl V> class VertexBufferV;
	class VertexBuffer;
	class IndexBuffer;

	class Texture2D;
	class RenderTarget;
	class DepthStencilBuffer;
	class DepthStencilState;
	class SpriteBatch;
	class SamplerState;
	class RenderTarget;
	class BlendState;

	class ShaderBase;
	class VertexShader;
	class HullShader;
	class DomainShader;
	class GeometryShader;
	class FragmentShader;

	namespace Primitives
	{
		class LineList;
		class LineStrip;
	}

	/// <summary>
	/// DirectX11 RHI (Rendering Hardware Interface)
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT GraphicsDevice final : public IGraphicsDevice
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11Device> _device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context;
		Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
#endif
		std::unique_ptr<DirectX11::RenderTarget> _backbufferRT;

		Math::Point _resolution;
		bool _fullscreen = false;

		std::unique_ptr<DepthStencilBuffer> _stencilBuffer;
		std::unique_ptr<DepthStencilState> _stencilState;
		std::unique_ptr<BlendState> _blendState;

		///Used for rendering post effects
		std::unique_ptr<DirectX11::VertexBufferV<VertexPointUV>> _screenQuad;
	public:
		GraphicsDevice() = delete;
		explicit GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);

		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;

		GraphicsDevice& operator=(const GraphicsDevice&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&&) = delete;

		void Clear(const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f }) override;
		void ClearRenderTarget(IRenderTarget* rt, const Math::Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f }) override;
		void ClearDepthBuffer(IDepthStencilBuffer* depth) override;

		void SetViewport() override;
		void SetViewport(const Viewport& viewport) override;

		void SetViewports(std::span<Viewport> viewports) override;
		Viewport GetViewport() override;
		
		/// <summary>
		/// Sets the current render target. Depth buffer is set to the default depth buffer.
		/// </summary>
		/// <param name="remderTarget">Render target pointer reference. Using null will use the backbuffer.</param>
		void SetRenderTarget(IRenderTarget* renderTarget) override;
		/// <summary>
		/// Unbinds the current render target and depth buffer. 
		/// </summary>
		/// <remarks>
		/// When called, there's no valid render surface that's assigned to the GPU. 
		/// </remarks>
		void UnbindRenderTargetAndDepth() override;
		/// <summary>
		/// Unbinds the current depth buffer.
		/// </summary>
		void UnbindDepthBuffer() override;
		/// <summary>
		/// Sets both render target and depth stencil buffer.
		/// </summary>
		/// <param name="renderTarget">Render surface to be drawn into. If null, it is set to the backbuffer.</param>
		/// <param name="depthBuffer">Depth stencil buffer. If null, will be set to the default non-null buffer.</param>
		void SetRenderTargetAndDepth(IRenderTarget* renderTarget, IDepthStencilBuffer* depthBuffer) override;
		/// <summary>
		/// Sets the render target, but unbinds the depth buffer.
		/// </summary>
		/// <param name="renderTarget">Render surface to be drawn into. If null, it is set to the backbuffer.</param>
		void SetRenderTargetAndDisableDepth(IRenderTarget* renderTarget) override;

		/// <summary>
		/// Draws a vertex buffer into the selected render target.
		/// </summary>
		/// <param name="vertexBuffer">Vertex buffer.</param>
		/// <param name="startSlot">Index of the first buffer.</param>
		void DrawVertexBuffer(IVertexBuffer* vertexBuffer, unsigned startSlot = 0) override;
		/// <summary>
		/// Draws a vertex buffer ordered by a index buffer into the selected render target.
		/// </summary>
		/// <param name="vertexBuffer">Vertex buffer.</param>
		/// <param name="indexBuffer">Index buffer.</param>
		void DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer) override;
		void DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer, unsigned numIndices) override;

		/// <summary>
		/// Sets a shader for the graphics pipeline.
		/// </summary>
		/// <param name="shader">Either a vertex shader, fragment shader, geometry shader, etc...</param>
		void SetShader(IShader* shader) override;

		void SetRasterizerState(const IRasterizerState* state) override;
		IRasterizerState* GetRasterizerState() override;

		void SetDepthStencilBuffer(IDepthStencilBuffer* depthBuffer) override;
		void SetDepthStencilState(IDepthStencilState* depthState, unsigned ref) override;

		void SetBlendState(IBlendState* blendState, const Math::Color& blendFactor = Math::Colors::Black, unsigned sampleMask = 0xFFFFFFFF) override;

		/// <summary>
		/// Sets the topology used by the vertex buffer.
		/// </summary>
		/// <param name="topology"></param>
		void SetTopology(VertexTopology topology) override;
		void DrawAuto() override;
		/// <summary>
		/// Swaps the front and backbuffer, thus outputting the backbuffer to the screen.
		/// </summary>
		void Present() override;

		/// <summary>
		/// Writes the backbuffer to a file. 
		/// </summary>
		/// <param name="path">PNG format image path.</param>
		void SaveBackBufferToFile(const std::filesystem::path& path) override;

		bool EnableVSync;

		/// <summary>
		/// Returns the backbuffer width and height.
		/// </summary>
		/// <returns></returns>
		Math::Point Resolution() const noexcept override;

		/// <summary>
		/// Resizes the back buffer, stencil buffer.
		/// </summary>
		/// <param name="newResolution">New resolution. Use 0,0 to match window size.</param>
		/// <remarks>
		/// Number of swap chain textures is preserved.
		/// Texture format will be same as the previous pixel format.
		/// </remarks>
		void ResizeBackBuffer(const Math::Point& newResolution) override;
		/// <summary>
		/// Switches the fullscreen state.
		/// </summary>
		void ToggleFullScreen() override;

		void SetScreenQuad() override;
		void DrawScreenQuad() override;

		IRenderTarget* GetBackBuffer() override;
		ITexture2D *GetBackBufferTexture() override;
		IDepthStencilBuffer& GetDepthBuffer() override;

		//Graphics::PixelFormat BackBufferFormat() const noexcept;

		std::unique_ptr<IBlendState> CreateBlendState(
			bool alphaCoverage, 
			bool indepedentBlend,
			std::array<RenderTargetBlendState, 8> renderTargetBlendStates
		) override;

		std::unique_ptr<IDepthStencilBuffer> CreateDepthStencilBuffer(
			size_t x,
			size_t y,
			PixelFormat format,
			BufferUsage usage
		) override;

		std::unique_ptr<IDepthStencilState> CreateDepthStencilState(
			bool EnableDepth, 
			DepthWriteMask Mask, 
			ComparisonFunction Function,
			bool EnableStencil,
			uint8_t ReadMask,
			uint8_t WriteMask,
			FaceOperation FrontFace,
			FaceOperation BackFace
		) override;

		virtual IShaderCompiler* ShaderCompiler() override;
		///<summmary>
		///Returns a 2x2 blank white texture.
		///</summary>
		virtual ITexture2D* WhiteBlank() override;

		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(std::span<unsigned> indices) override;
		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(size_t numIndices, BufferUsage usage) override;

		virtual std::unique_ptr<IRenderTarget> CreateRenderTarget(
			size_t x,
			size_t y,
			PixelFormat format
		) override;

		virtual std::unique_ptr<ITexture2D> CreateTexture2D(
			size_t x,
			size_t y,
			void* data,
			PixelFormat format,
			BufferUsage usage
		) override;

		virtual std::unique_ptr<IVertexBuffer> CreateVertexBuffer(
			const void* data,
			size_t structSize,
			size_t numVertices,
			BufferUsage usage
		) override;

		~GraphicsDevice() override;

		template<VertexDecl V> friend class VertexBufferV;

		friend class VertexBuffer;
		friend class IndexBuffer;
		friend class Texture2D;
		friend class RenderTarget;
		friend class RasterizerState;
		friend class DepthStencilState;
		friend class SamplerState;
		friend class SpriteBatch;
		friend class DepthStencilBuffer;
		friend class BlendState;

		friend class ShaderBase;
		friend class VertexShader;
		friend class HullShader;
		friend class DomainShader;
		friend class GeometryShader;
		friend class FragmentShader;
	};
}
