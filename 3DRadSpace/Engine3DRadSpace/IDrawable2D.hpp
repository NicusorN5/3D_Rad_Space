/// ------------------------------------------------------------------------------------------------
/// File:   IDrawable2D.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "Graphics/SpriteBatch.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT IDrawable2D
	{
	public:
		virtual void Draw2D() = 0;

		~IDrawable2D() = default;
	};
}