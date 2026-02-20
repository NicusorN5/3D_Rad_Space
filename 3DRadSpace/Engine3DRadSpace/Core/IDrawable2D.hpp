#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace
{
	class E3DRSP_CORE_EXPORT IDrawable2D
	{
	public:
		virtual void Draw2D() = 0;
		virtual ~IDrawable2D() = default;
	};
}