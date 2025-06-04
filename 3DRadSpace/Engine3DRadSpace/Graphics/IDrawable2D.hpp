#pragma once
#include "SpriteBatch.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT IDrawable2D
	{
	public:
		virtual void Draw2D() = 0;

		~IDrawable2D() = default;
	};
}