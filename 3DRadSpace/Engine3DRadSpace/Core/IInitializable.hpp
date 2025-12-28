#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	class E3DRSP_OBJECTS_EXPORT IInitializable
	{
	public:
		virtual void Initialize() = 0;
		inline virtual ~IInitializable() = default;
	};
}