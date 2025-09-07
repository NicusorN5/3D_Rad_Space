#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents the type of a input layout element.
	/// </summary>
	enum class InputLayoutElement
	{
		Position_Vec2 = 0,
		Position_Vec3,
		Position_Vec4,

		PositionTransformed_Vec3,
		PositionTransformed_Vec4,

		Color,

		Normal_Vec3,
		Normal_Vec4,

		Tangent_Vec3,
		Tangent_Vec4,

		Bitangent_Vec3,
		Bitangent_Vec4,

		TextureCoordinate2D,
		TextureCoordinate3D,
		TextureCoordinate4D,

		BlendIndices,
		BlendWeights,
		PointSize,
	};

	/// <summary>
	/// Represents a vertex shader.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT IVertexShader : public IShader
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
		IVertexShader(
			GraphicsDevice* device, 
			std::span<InputLayoutElement> inputLayout,
			const char* shaderSourceCode,
			const char* vsEntry,
			ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4
		);
		
		IVertexShader(
			GraphicsDevice* device,
			std::span<InputLayoutElement> inputLayout, 
			const std::filesystem::path& path, 
			const char* vsEntry,
			ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4
		);
	
		IVertexShader(IVertexShader &) = delete;
		IVertexShader(IVertexShader &&) noexcept = delete;

		IVertexShader &operator=(IVertexShader &) = delete;
		IVertexShader &operator=(IVertexShader &&) noexcept = delete;
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