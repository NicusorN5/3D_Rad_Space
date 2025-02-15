/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/Rendering/IRenderingEffect.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "../Effect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Represents the base type of a rendering effect, such as fog, outline, et cetera.
	/// </summary>
	class DLLEXPORT IRenderingEffect
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
