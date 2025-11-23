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
		std::unique_ptr<IDepthStencilBuffer> _depthStencilBuffer;
		std::unique_ptr<IShaderCompiler> _compiler;
		std::unique_ptr<ITexture2D> _whiteBlankTexture;
		std::unique_ptr<IGraphicsCommandList> _context;
	public:
		GraphicsDevice() = delete;
		explicit GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);

		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;

		GraphicsDevice& operator=(const GraphicsDevice&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&&) = delete;

		bool EnableVSync;

		//virtual std::unique_ptr<IRasterizerState> GetRasterizerState() override;

		virtual Math::Point Resolution() const noexcept override;

		virtual IRenderTarget* GetBackBuffer() override;
		virtual ITexture2D *GetBackBufferTexture() override;
		virtual IDepthStencilBuffer& GetDepthBuffer() override;
		std::unique_ptr<IRasterizerState> GetRasterizerState() override;

		virtual std::unique_ptr<IBlendState> CreateBlendState(
			bool alphaCoverage, 
			bool indepedentBlend,
			std::array<RenderTargetBlendState, 8> renderTargetBlendStates
		) override;

		virtual std::unique_ptr<IBlendState> CreateBlendState_Opaque() override;
		virtual std::unique_ptr<IBlendState> CreateBlendState_AlphaBlend() override;
		virtual std::unique_ptr<IBlendState> CreateBlendState_Additive() override;
		virtual std::unique_ptr<IBlendState> CreateBlendState_NonPremultiplied() override;

		virtual std::unique_ptr<IDepthStencilBuffer> CreateDepthStencilBuffer(
			size_t x,
			size_t y
		) override;

		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState(
			bool EnableDepth, 
			DepthWriteMask Mask, 
			ComparisonFunction Function,
			bool EnableStencil,
			uint8_t ReadMask,
			uint8_t WriteMask,
			FaceOperation FrontFace,
			FaceOperation BackFace
		) override;

		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthDefault() override;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthNone() override;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthRead() override;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthReverseZ() override;
		virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthReadReverseZ() override;

		virtual IShaderCompiler* ShaderCompiler() override;
		///<summmary>
		///Returns a 2x2 blank white texture.
		///</summary>
		virtual ITexture2D* WhiteBlank() override;

		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(std::span<unsigned> indices) override;
		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(size_t numIndices, BufferUsage usage) override;

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
		) override;

		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullNone() override;
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullClockwise() override;
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_CullCounterClockwise() override;
		virtual std::unique_ptr<IRasterizerState> CreateRasterizerState_Wireframe() override;

		virtual std::unique_ptr<IRenderTarget> CreateRenderTarget(
			size_t x,
			size_t y,
			PixelFormat format
		) override;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState() override;

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
		) override;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState_LinearClamp() override;
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_LinearWrap() override;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState_PointClamp() override;
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_PointWrap() override;

		virtual std::unique_ptr<ISamplerState> CreateSamplerState_AnisotropicClamp() override;
		virtual std::unique_ptr<ISamplerState> CreateSamplerState_AnisotropicWrap() override;

		virtual std::unique_ptr<ITexture2D> CreateTexture2D(
			size_t x,
			size_t y,
			void* data,
			PixelFormat format,
			BufferUsage usage
		) override;

		virtual std::unique_ptr<ITexture2D> CreateTexture2D(const std::filesystem::path& path) override;

		virtual std::unique_ptr<IVertexBuffer> CreateVertexBuffer(
			const void* data,
			size_t structSize,
			size_t numVertices,
			BufferUsage usage
		) override;

		virtual std::unique_ptr<IGraphicsCommandList> CreateCommandList() override;
		virtual IGraphicsCommandList* ImmediateContext() override;

		~GraphicsDevice() override;
	};
}