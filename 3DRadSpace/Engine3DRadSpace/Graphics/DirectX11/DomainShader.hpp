#pragma once
#include "ShaderBase.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	/// <summary>
	/// Represents a domain shader.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT DomainShader : public ShaderBase
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11DomainShader> _shader;
		const char *_determineTarget();
#endif
		void _createShader();
	public:
		DomainShader(GraphicsDevice* device, const char* source, const char* fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);
		DomainShader(GraphicsDevice* device, const std::filesystem::path& path, const char* fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);

		DomainShader(DomainShader&) = delete;
		DomainShader(DomainShader&&) noexcept = delete;

		DomainShader &operator = (DomainShader&) = delete;
		DomainShader &operator = (DomainShader&&) noexcept = delete;

		void SetTexture(unsigned index, ITexture2D *texture) override;
		void SetTextures(std::span<ITexture2D*> textures) override;
		void SetSampler(unsigned index, ISamplerState *samplerState) override;
		void SetShader() override;
		void* GetHandle() const noexcept override;

		~DomainShader() = default;

		friend class GraphicsDevice;
	};
}

