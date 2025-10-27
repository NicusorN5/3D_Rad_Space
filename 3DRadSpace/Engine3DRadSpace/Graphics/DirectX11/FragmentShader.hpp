#pragma once
#include "../IFragmentShader.hpp"
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

	class E3DRSP_GRAPHICS_EXPORT FragmentShader : public ShaderBase, public IFragmentShader
	{
		Microsoft::WRL::ComPtr<ID3D11PixelShader> _shader;
		void _createShader();
		const char *_determineTarget();
	protected:
		FragmentShader(GraphicsDevice* device, const char* shaderSource, const char* entryFunction, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);
		FragmentShader(GraphicsDevice* device, const std::filesystem::path& path, const char* entryFunction, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);

		FragmentShader(FragmentShader&) = delete;
		FragmentShader(FragmentShader&&) noexcept = default;

		FragmentShader &operator = (FragmentShader&) = delete;
		FragmentShader &operator = (FragmentShader&&) noexcept = default;
	public:
		void SetTexture(unsigned index, ITexture2D *texture) override;
		void SetTextures(std::span<ITexture2D*> textures) override;
		void SetSampler(unsigned index, ISamplerState *samplerState) override;
		void SetShader() override;
		void* GetHandle() const noexcept override;

		virtual ~FragmentShader() = default;

		friend class GraphicsDevice;
	};
}
