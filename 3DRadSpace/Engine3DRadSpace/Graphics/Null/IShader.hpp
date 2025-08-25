#pragma once
#include "../ShaderFeatureLevel.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class Texture2D;
	class SamplerState;
	class E3DRSP_GRAPHICS_NULL_EXPORT IShader
	{
	protected:
		IShader() = default;
	public:
		void SetData(unsigned index, const void *data, unsigned dataSize);
		virtual void SetTexture(unsigned index, Texture2D *texture) = 0;
		virtual void SetSampler(unsigned index, SamplerState *samplerState) = 0;
		virtual void SetShader() = 0;
		virtual void* GetHandle() const noexcept = 0;

		ShaderFeatureLevel GetFeatureLevel();
		std::string GetEntryName();

		const char* GetCompilationErrorsAndWarnings();

		virtual ~IShader() = default;
	};
}