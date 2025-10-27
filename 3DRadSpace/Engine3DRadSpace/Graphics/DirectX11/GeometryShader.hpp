#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT GeometryShader : public IShader
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> _shader;
		const char *_determineTarget();
#endif
		void _createShader();
	protected:
		GeometryShader(GraphicsDevice* device, const char* source, const char* fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);
		GeometryShader(GraphicsDevice* device, const std::filesystem::path& path, const char* fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);

		GeometryShader(GeometryShader&) = delete;
		GeometryShader(GeometryShader&&) noexcept = delete;
		GeometryShader&operator = (GeometryShader&) = delete;
		GeometryShader&operator = (GeometryShader&&) noexcept = delete;
	public:
		void SetTexture(unsigned index, ITexture2D *texture) override;
		void SetSampler(unsigned index, ISamplerState *samplerState) override;
		void SetShader() override;
		void* GetHandle() const noexcept override;

		~GeometryShader() override = default;

		friend class GraphicsDevice;
	};
}

