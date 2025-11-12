#pragma once
#include "DirectX11.h"
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

	/// <summary>
	/// DirectX11 RHI (Rendering Hardware Interface)
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT GraphicsDevice final : public IGraphicsDevice
	{
		Microsoft::WRL::ComPtr<ID3D11Device> _device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context;
		Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;

		std::unique_ptr<DirectX11::RenderTarget> _backbufferRT;

		Math::Point _resolution;
		bool _fullscreen = false;

		std::unique_ptr<DepthStencilBuffer> _stencilBuffer;
		std::unique_ptr<DepthStencilState> _stencilState;
		std::unique_ptr<BlendState> _blendState;

		///Used for rendering post effects
		std::unique_ptr<VertexBuffer> _screenQuad;
	public:
		GraphicsDevice() = delete;
		explicit GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);

		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;

		GraphicsDevice& operator=(const GraphicsDevice&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&&) = delete;

		bool EnableVSync;

		/// <summary>
		/// Returns the backbuffer width and height.
		/// </summary>
		/// <returns></returns>
		Math::Point Resolution() const noexcept override;

		IRenderTarget* GetBackBuffer() override;
		ITexture2D *GetBackBufferTexture() override;
		IDepthStencilBuffer& GetDepthBuffer() override;

		std::unique_ptr<IRasterizerState> GetRasterizerState() override;

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

		virtual std::unique_ptr<IGraphicsCommandList> CreateCommandList() override;

		~GraphicsDevice() override;

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
