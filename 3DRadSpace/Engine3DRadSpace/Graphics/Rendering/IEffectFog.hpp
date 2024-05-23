#pragma once
#include "IRenderingEffect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class DLLEXPORT IEffectFog : public IRenderingEffect
	{
	protected:
		IEffectFog() = default;

		IEffectFog(const IEffectFog&) = delete;
		IEffectFog& operator=(const IEffectFog&) = delete;

		IEffectFog(IEffectFog&&) noexcept = default;
		IEffectFog& operator=(IEffectFog&&) noexcept = default;
	public:
		Color FogColor;
		float FogBegin;
		float FogEnd;

		~IEffectFog() override = default;
	};
}