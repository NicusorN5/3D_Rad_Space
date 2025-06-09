#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace
{
	class E3DRSP_OBJECTS_EXPORT IInitiializable
	{
	public:
		virtual void Initialize() = 0;
		inline virtual ~IInitiializable() = default;
	};
}