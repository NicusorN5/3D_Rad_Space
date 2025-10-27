#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents a domain shader.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT DomainShader : public IShader
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11DomainShader> _shader;
		const char *_determineTarget();
#endif
		void _createShader();
	protected:
		IDomainShader(GraphicsDevice* device, const char* source, const char* fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);
		IDomainShader(GraphicsDevice* device, const std::filesystem::path& path, const char* fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);

		IDomainShader(DomainShader&) = delete;
		IDomainShader(DomainShader&&) noexcept = delete;

		IDomainShader &operator = (DomainShader&) = delete;
		IDomainShader &operator = (DomainShader&&) noexcept = delete;
	public:
		void SetTexture(unsigned index, ITexture2D *texture) override;
		void SetSampler(unsigned index, ISamplerState *samplerState) override;
		void SetShader() override;
		void* GetHandle() const noexcept override;

		~DomainShader() = default;

		friend class GraphicsDevice;
	};
}

