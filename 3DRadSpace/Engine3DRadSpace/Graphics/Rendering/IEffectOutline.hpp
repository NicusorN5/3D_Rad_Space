#pragma once
#include "IRenderingEffect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Represents a base type of a Outline rendering effect.
	/// </summary>
	class DLLEXPORT IEffectOutline : public IRenderingEffect
	{
	protected:
		IEffectOutline() = default;
	public:
		Color OutlineColor;
		float OutlineWidth;

		~IEffectOutline() override = default;
	};
}