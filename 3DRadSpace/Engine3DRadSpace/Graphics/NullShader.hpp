#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IGraphicsDevice;

	class E3DRSP_GRAPHICS_EXPORT NullShader final : public IShader
	{
	public:
		NullShader() = default;

		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		void SetData(unsigned index, const void *data, size_t dataSize) override;
		void SetTexture(unsigned index, ITexture2D *texture) override;
		void SetTextures(std::span<ITexture2D*> textures) override;
		void SetSampler(unsigned index, ISamplerState *samplerState) override;
		void SetShader() override;
		std::vector<Reflection::IReflectedField*> GetVariables() const override;
		void Set(const std::string& name, const void* data, size_t dataSize) override;

		std::string GetEntryName() override;
		const char* GetCompilationErrorsAndWarnings() override;

		~NullShader() override = default;
	};
}