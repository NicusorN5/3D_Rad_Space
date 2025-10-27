#pragma once
#include "ShaderBase.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT HullShader : public ShaderBase
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11HullShader> _shader;

		void _createShader();
#endif
		const char *_determineTarget();
	protected:
		HullShader(GraphicsDevice* device, const char* shaderSource, const char* hsEntry, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);
		HullShader(GraphicsDevice* device, const std::filesystem::path& path, const char* hsEntry, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);

		IHullShader(HullShader&) = delete;
		IHullShader(HullShader&&) noexcept = delete;

		HullShader&operator=(HullShader&) = delete;
		HullShader&operator=(HullShader&&) noexcept = delete;
	public:
		void SetTexture(unsigned index, Texture2D *texture) override;
		void SetSampler(unsigned index, SamplerState *samplerState) override;
		void SetShader() override;
		void* GetHandle() const noexcept override;

		~HullShader() = default;
	};
}

