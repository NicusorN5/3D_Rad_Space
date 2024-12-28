#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT IFragmentShader : public IShader
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11PixelShader> _shader;

		void _createShader();
#endif
		const char *_determineTarget();
	protected:
		IFragmentShader(GraphicsDevice* device, const char* shaderSource, const char* entryFunction, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);
		IFragmentShader(GraphicsDevice* device, const std::filesystem::path& path, const char* entryFunction, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);
	public:
		IFragmentShader(IFragmentShader &) = delete;
		IFragmentShader(IFragmentShader &&) noexcept = delete;

		IFragmentShader &operator = (IFragmentShader &) = delete;
		IFragmentShader &operator = (IFragmentShader &&) noexcept = delete;

		void SetTexture(unsigned index, Texture2D *texture) override;
		void SetSampler(unsigned index, SamplerState *samplerState) override;
		void SetShader() override;
		void* GetHandle() const noexcept override;

		virtual ~IFragmentShader() = default;

		friend class GraphicsDevice;
	};
}
