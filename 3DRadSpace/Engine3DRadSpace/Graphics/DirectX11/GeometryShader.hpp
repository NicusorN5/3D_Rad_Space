#pragma once
#include "ShaderBase.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class E3DRSP_GRAPHICS_DX11_EXPORT GeometryShader : public ShaderBase
	{
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> _shader;
		static const char *_determineTarget(ShaderFeatureLevel f);

		void _createShader();
	public:
		GeometryShader(GraphicsDevice* device, const char* source, const char* fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);
		GeometryShader(GraphicsDevice* device, const std::filesystem::path& path, const char* fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);

		GeometryShader(GeometryShader&) = delete;
		GeometryShader(GeometryShader&&) noexcept = delete;
		GeometryShader& operator = (GeometryShader&) = delete;
		GeometryShader& operator = (GeometryShader&&) noexcept = delete;

		void SetTexture(unsigned index, ITexture1D *texture) override;
		void SetTextures(std::span<ITexture1D*> textures) override;

		void SetTexture(unsigned index, ITexture2D *texture) override;
		void SetTextures(std::span<ITexture2D*> textures) override;

		void SetTexture(unsigned index, ITextureCube* texture) override;
		void SetTextures(std::span<ITextureCube*> textures) override;

		void SetSampler(unsigned index, ISamplerState *samplerState) override;
		void SetShader() override;
		void* GetHandle() const noexcept override;

		~GeometryShader() override = default;

		friend class GraphicsDevice;
	};
}

