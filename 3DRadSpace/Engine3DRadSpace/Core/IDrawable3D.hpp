#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace
{
	class E3DRSP_CORE_EXPORT IDrawable3D
	{
	public:
		virtual void Draw3D() = 0;
		virtual ~IDrawable3D() = default;
	};
}
