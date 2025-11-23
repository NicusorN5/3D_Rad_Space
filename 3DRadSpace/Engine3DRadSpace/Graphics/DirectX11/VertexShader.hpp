#pragma once
#include "ShaderBase.hpp"
#include "InputLayoutElement.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	/// <summary>
	/// Represents a vertex shader.
	/// </summary>
	class E3DRSP_GRAPHICS_DX11_EXPORT VertexShader : public ShaderBase
	{
		Microsoft::WRL::ComPtr<ID3D11VertexShader> _shader;

		Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayout;
		void _createShader();

		const char *_determineTarget();
		[[nodiscard]] D3D11_INPUT_ELEMENT_DESC *_generateInputElementDesc(std::span<InputLayoutElement> inputLayout);
		void _generateInputLayout(std::span<InputLayoutElement> inputLayout);
	public:
		/// <summary>
		/// Constructs a vertex shader from a string containing the source code.
		/// </summary>
		/// <param name="device">Graphics device</param>
		/// <param name="inputLayout">Vertex input layout</param>
		/// <param name="shaderSourceCode">HLSL source</param>
		/// <param name="vsEntry">HLSL entry function</param>
		/// <param name="featureLevel">HLSL feature level.</param>
		VertexShader(
			GraphicsDevice* device, 
			const char* shaderSourceCode,
			const char* vsEntry,
			ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4
		);
		
		VertexShader(
			GraphicsDevice* device,
			const std::filesystem::path& path, 
			const char* vsEntry,
			ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4
		);
	
		VertexShader(VertexShader&) = delete;
		VertexShader(VertexShader&&) noexcept = delete;

		VertexShader &operator=(VertexShader&) = delete;
		VertexShader &operator=(VertexShader&&) noexcept = delete;

		void SetTexture(unsigned index, ITexture2D *texture) override;
		void SetTextures(std::span<ITexture2D*> textures) override;
		void SetSampler(unsigned index, ISamplerState *samplerState) override;
		void SetShader() override;
		
		void* GetHandle() const noexcept override;

		virtual ~VertexShader() = default;

		friend class GraphicsDevice;
		friend class GraphicsCommandList;
	};
}