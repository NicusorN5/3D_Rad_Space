#pragma once
#include "../Effect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Represents the base type of a rendering effect, such as fog, outline, et cetera.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT IRenderingEffect
	{
	protected:
		IRenderingEffect() = default;
		IRenderingEffect(IRenderingEffect&&) noexcept = default;

		IRenderingEffect& operator=(IRenderingEffect&&) noexcept = default;
	public:
		IRenderingEffect(IRenderingEffect&) = delete;
		IRenderingEffect& operator=(IRenderingEffect&) = delete;

		/// <summary>
		/// Applies the effect to the graphics pipeline.
		/// </summary>
		virtual void Apply() = 0;

		virtual ~IRenderingEffect() = default;
	};
}
