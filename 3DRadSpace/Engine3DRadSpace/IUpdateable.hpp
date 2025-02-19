#pragma once
#include "Libs.hpp"
#include "Input/Keyboard.hpp"
#include "Input/Mouse.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT IUpdateable
	{
	public:
		virtual void Update() = 0;
		inline virtual ~IUpdateable() = default;
	};
}

