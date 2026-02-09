#pragma once
#include "ShaderBase.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class E3DRSP_GRAPHICS_DX11_EXPORT HullShader : public ShaderBase
	{
		Microsoft::WRL::ComPtr<ID3D11HullShader> _shader;

		void _createShader();
		static const char *_determineTarget(ShaderFeatureLevel f);
	public:
		HullShader(GraphicsDevice* device, const char* shaderSource, const char* hsEntry, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);
		HullShader(GraphicsDevice* device, const std::filesystem::path& path, const char* hsEntry, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);

		HullShader(HullShader&) = delete;
		HullShader(HullShader&&) noexcept = delete;

		HullShader &operator=(HullShader&) = delete;
		HullShader &operator=(HullShader&&) noexcept = delete;

		void SetTexture(unsigned index, ITexture1D *texture) override;
		void SetTextures(std::span<ITexture1D*> textures) override;

		void SetTexture(unsigned index, ITexture2D *texture) override;
		void SetTextures(std::span<ITexture2D*> textures) override;

		void SetTexture(unsigned index, ITextureCube* texture) override;
		void SetTextures(std::span<ITextureCube*> textures) override;

		void SetSampler(unsigned index, ISamplerState *samplerState) override;
		void SetShader() override;
		void* GetHandle() const noexcept override;

		~HullShader() = default;
	};
}

