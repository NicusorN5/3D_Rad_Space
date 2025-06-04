#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT IUpdateable
	{
	public:
		virtual void Update() = 0;
		inline virtual ~IUpdateable() = default;
	};
}

