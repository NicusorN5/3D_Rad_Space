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
		std::unique_ptr<IVertexBuffer> _screenQuad;
	public:
		GraphicsDevice() = delete;
		explicit GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);

		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;

		GraphicsDevice& operator=(const GraphicsDevice&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&&) = delete;

		bool EnableVSync;

		//std::unique_ptr<IRasterizerState> GetRasterizerState() override;

		Math::Point Resolution() const noexcept override;

		IRenderTarget* GetBackBuffer() override;
		ITexture2D *GetBackBufferTexture() override;
		IDepthStencilBuffer& GetDepthBuffer() override;
		std::unique_ptr<IRasterizerState> GetRasterizerState() override;

		std::unique_ptr<IBlendState> CreateBlendState(
			bool alphaCoverage, 
			bool indepedentBlend,
			std::array<RenderTargetBlendState, 8> renderTargetBlendStates
		) override;

		std::unique_ptr<IBlendState> CreateBlendState_Opaque() override;
		std::unique_ptr<IBlendState> CreateBlendState_AlphaBlend() override;
		std::unique_ptr<IBlendState> CreateBlendState_Additive() override;
		std::unique_ptr<IBlendState> CreateBlendState_NonPremultiplied() override;

		std::unique_ptr<IDepthStencilBuffer> CreateDepthStencilBuffer(
			size_t x,
			size_t y
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

		std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthDefault() override;
		std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthNone() override;
		std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthRead() override;
		std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthReverseZ() override;
		std::unique_ptr<IDepthStencilState> CreateDepthStencilState_DepthReadReverseZ() override;

		IShaderCompiler* ShaderCompiler() override;
		///<summmary>
		///Returns a 2x2 blank white texture.
		///</summary>
		ITexture2D* WhiteBlank() override;

		std::unique_ptr<IIndexBuffer> CreateIndexBuffer(std::span<unsigned> indices) override;
		std::unique_ptr<IIndexBuffer> CreateIndexBuffer(size_t numIndices, BufferUsage usage) override;

		std::unique_ptr<IRasterizerState> CreateRasterizerState(
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

		std::unique_ptr<IRasterizerState> CreateRasterizerState_CullNone() override;
		std::unique_ptr<IRasterizerState> CreateRasterizerState_CullClockwise() override;
		std::unique_ptr<IRasterizerState> CreateRasterizerState_CullCounterClockwise() override;
		std::unique_ptr<IRasterizerState> CreateRasterizerState_Wireframe() override;

		std::unique_ptr<IRenderTarget> CreateRenderTarget(
			size_t x,
			size_t y,
			PixelFormat format
		) override;

		std::unique_ptr<ISamplerState> CreateSamplerState() override;

		std::unique_ptr<ISamplerState> CreateSamplerState(
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

		std::unique_ptr<ISamplerState> CreateSamplerState_LinearClamp() override;
		std::unique_ptr<ISamplerState> CreateSamplerState_LinearWrap() override;

		std::unique_ptr<ISamplerState> CreateSamplerState_PointClamp() override;
		std::unique_ptr<ISamplerState> CreateSamplerState_PointWrap() override;

		std::unique_ptr<ISamplerState> CreateSamplerState_AnisotropicClamp() override;
		std::unique_ptr<ISamplerState> CreateSamplerState_AnisotropicWrap() override;

		std::unique_ptr<ITexture2D> CreateTexture2D(
			size_t x,
			size_t y,
			void* data,
			PixelFormat format,
			BufferUsage usage
		) override;

		std::unique_ptr<ITexture2D> CreateTexture2D(const std::filesystem::path& path) override;

		std::unique_ptr<IVertexBuffer> CreateVertexBuffer(
			const void* data,
			size_t structSize,
			size_t numVertices,
			BufferUsage usage
		) override;

		std::unique_ptr<IGraphicsCommandList> CreateCommandList() override;
		IGraphicsCommandList* ImmediateContext() override;

		IVertexBuffer* GetScreenQuad() const noexcept override;

		~GraphicsDevice() override;
	};
}