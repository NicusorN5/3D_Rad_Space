#pragma once
#include "PostProcessEffect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Implements a screen space fog effect.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT LinearPixelFogEffect : public PostProcessEffect
	{
	protected:
		LinearPixelFogEffect(const LinearPixelFogEffect&) = delete;
		LinearPixelFogEffect& operator=(const LinearPixelFogEffect&) = delete;

		LinearPixelFogEffect(LinearPixelFogEffect&&) noexcept = default;
		LinearPixelFogEffect& operator=(LinearPixelFogEffect&&) noexcept = default;
	public:
		/// <summary>
		/// Loads the screen space linear interpolated fog shader.
		/// </summary>
		/// <param name="device"></param>
		LinearPixelFogEffect(GraphicsDevice* device);

		/// <summary>
		/// Color of the fog.
		/// </summary>
		Math::Color FogColor;
		/// <summary>
		/// Fog begin range, between 0.0 and 1.0 in normalized device coordinates.
		/// </summary>
		float FogBegin;
		/// <summary>
		/// Fog end range, between 0.0 and 1.0 in normalized device coordiniates.
		/// </summary>
		float FogEnd;

		/// <summary>
		/// Used to linearlize the depth buffer.
		/// </summary>
		float NearPlaneDistance;
		/// <summary>
		/// Used to linearlize the depth buffer.
		/// </summary>
		float FarPlaneDistance;

		/// <summary>
		/// Applies this effect to the render target.
		/// </summary>
		void Apply() override;

		~LinearPixelFogEffect() override = default;
	};
}