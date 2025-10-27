#pragma once
#include "DX11ShaderBase.hpp"
#include "InputLayoutElement.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	/// <summary>
	/// Represents a vertex shader.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT VertexShader : public DX11ShaderBase
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11VertexShader> _shader;

		Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayout;
#endif
		void _createShader();
#ifdef USING_DX11
		const char *_determineTarget();
		[[nodiscard]] D3D11_INPUT_ELEMENT_DESC *_generateInputElementDesc(std::span<InputLayoutElement> inputLayout);
#endif
		void _generateInputLayout(std::span<InputLayoutElement> inputLayout);
	protected:
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
			std::span<InputLayoutElement> inputLayout,
			const char* shaderSourceCode,
			const char* vsEntry,
			ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4
		);
		
		VertexShader(
			GraphicsDevice* device,
			std::span<InputLayoutElement> inputLayout, 
			const std::filesystem::path& path, 
			const char* vsEntry,
			ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4
		);
	
		VertexShader(VertexShader&) = delete;
		VertexShader(VertexShader&&) noexcept = delete;

		VertexShader &operator=(VertexShader&) = delete;
		VertexShader &operator=(VertexShader&&) noexcept = delete;
	public:
		virtual std::span<InputLayoutElement> InputLayout() = 0;

		void SetTexture(unsigned index, Texture2D *texture) override;
		void SetSampler(unsigned index, SamplerState *samplerState) override;
		void SetShader() override;
		void* GetHandle() const noexcept override;

		virtual ~IVertexShader() = default;

		friend class GraphicsDevice;
	};
}