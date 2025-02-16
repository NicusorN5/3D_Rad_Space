/// ------------------------------------------------------------------------------------------------
/// File:   Memory.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace::Memory
{
	constexpr bool IsBigEndian()
	{
        int a = 1;
        return !((char*)&a)[0];
    }
}