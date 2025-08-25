#pragma once
#include "IRenderingEffect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Represents a base type of a Outline rendering effect.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT IEffectOutline : public IRenderingEffect
	{
	protected:
		IEffectOutline() = default;
	public:
		Math::Color OutlineColor;
		float OutlineWidth;

		~IEffectOutline() override = default;
	};
}