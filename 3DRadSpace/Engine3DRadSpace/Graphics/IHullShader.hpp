#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IHullShader : public IShader
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11HullShader> _shader;

		void _createShader();
#endif
		const char *_determineTarget();
	protected:
		IHullShader(GraphicsDevice* device, const char* shaderSource, const char* hsEntry, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);
		IHullShader(GraphicsDevice* device, const std::filesystem::path& path, const char* hsEntry, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);
	public:
		IHullShader(IHullShader &) = delete;
		IHullShader(IHullShader &&) noexcept = delete;
		IHullShader &operator=(IHullShader &) = delete;
		IHullShader &operator=(IHullShader &&) noexcept = delete;

		void SetTexture(unsigned index, Texture2D *texture) override;
		void SetSampler(unsigned index, SamplerState *samplerState) override;
		void SetShader() override;
		void* GetHandle() const noexcept override;

		~IHullShader() = default;
	};
}

