#pragma once
#include "ShaderFeatureLevel.hpp"
#include "IGPUResource.hpp"

namespace Engine3DRadSpace::Graphics
{
	class ITexture2D;
	class ISamplerState;

	class E3DRSP_GRAPHICS_EXPORT IShader : IGPUResource
	{
	protected:
	public:
		IShader(const IShader&) = delete;
		IShader(IShader&&) noexcept = default;

		IShader& operator=(const IShader&) = delete;
		IShader& operator=(IShader&&) noexcept = default;

		void SetData(unsigned index, const void *data, unsigned dataSize);
		virtual void SetTexture(unsigned index, ITexture2D *texture) = 0;
		virtual void SetSampler(unsigned index, ISamplerState *samplerState) = 0;

		virtual ~IShader() = default;
	};
}