#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	class E3DRSP_CORE_EXPORT IInitializable
	{
	public:
		virtual void Initialize() = 0;
		inline virtual ~IInitializable() = default;
	};
}