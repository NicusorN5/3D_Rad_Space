#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace
{
	class E3DRSP_OBJECTS_EXPORT IDrawable2D
	{
	public:
		virtual void Draw2D() = 0;
		~IDrawable2D() = default;
	};
}