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

		void SetData(unsigned index, const void *data, unsigned dataSize) override;
		void SetTexture(unsigned index, ITexture2D *texture) override;
		void SetSampler(unsigned index, ISamplerState *samplerState) override;

		~NullShader() override = default;
	};
}