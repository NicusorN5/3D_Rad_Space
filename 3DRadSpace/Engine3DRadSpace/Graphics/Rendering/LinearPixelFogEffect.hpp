#pragma once
#include "PostProcessEffect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Implements a screen space fog effect.
	/// </summary>
	class DLLEXPORT LinearPixelFogEffect : public PostProcessEffect
	{
	protected:
		LinearPixelFogEffect(const LinearPixelFogEffect&) = delete;
		LinearPixelFogEffect& operator=(const LinearPixelFogEffect&) = delete;

		LinearPixelFogEffect(LinearPixelFogEffect&&) noexcept = default;
		LinearPixelFogEffect& operator=(LinearPixelFogEffect&&) noexcept = default;
	public:
		LinearPixelFogEffect(GraphicsDevice* device);

		Color FogColor;
		float FogBegin;
		float FogEnd;

		~LinearPixelFogEffect() override = default;
	};
}