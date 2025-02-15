/// ------------------------------------------------------------------------------------------------
/// File:   IUpdateable.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
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

