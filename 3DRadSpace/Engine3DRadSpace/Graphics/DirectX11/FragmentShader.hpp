#pragma once
#include "ShaderBase.hpp"

namespace Engine3DRadSpace
{
	namespace Graphics
	{
		class ITexture2D;
	}
}

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class GraphicsDevice;
	class Texture2D;
	class SamplerState;

	class E3DRSP_GRAPHICS_DX11_EXPORT FragmentShader : public ShaderBase
	{
		Microsoft::WRL::ComPtr<ID3D11PixelShader> _shader;
		void _createShader();
		static const char *_determineTarget(ShaderFeatureLevel f);
	public:
		FragmentShader(GraphicsDevice* device, const char* shaderSource, const char* entryFunction, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);
		FragmentShader(GraphicsDevice* device, const std::filesystem::path& path, const char* entryFunction, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);

		FragmentShader(FragmentShader&) = delete;
		FragmentShader(FragmentShader&&) noexcept = default;

		FragmentShader& operator = (FragmentShader&) = delete;
		FragmentShader& operator = (FragmentShader&&) noexcept = default;

		void SetTexture(unsigned index, ITexture1D *texture) override;
		void SetTextures(std::span<ITexture1D*> textures) override;

		void SetTexture(unsigned index, ITexture2D *texture) override;
		void SetTextures(std::span<ITexture2D*> textures) override;

		void SetTexture(unsigned index, ITextureCube* texture) override;
		void SetTextures(std::span<ITextureCube*> textures) override;

		void SetSampler(unsigned index, ISamplerState *samplerState) override;
		void SetShader() override;
		void* GetHandle() const noexcept override;

		~FragmentShader() override = default;

		friend class GraphicsDevice;
	};
}
