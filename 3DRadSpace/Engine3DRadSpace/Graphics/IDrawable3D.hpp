#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT IDrawable3D
	{
	public:
		virtual void Draw3D() = 0;
		virtual ~IDrawable3D() = default;
	};
}
