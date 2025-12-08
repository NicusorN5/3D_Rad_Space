#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	class E3DRSP_OBJECTS_EXPORT IUpdateable
	{
	public:
		virtual void Update() = 0;
		inline virtual ~IUpdateable() = default;
	};
}