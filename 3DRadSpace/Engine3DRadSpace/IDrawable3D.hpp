/// ------------------------------------------------------------------------------------------------
/// File:   IDrawable3D.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "GraphicsDevice.hpp"
#include "Math\Matrix4x4.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT IDrawable3D
	{
	public:
		virtual void Draw3D() = 0;
		virtual ~IDrawable3D() = default;
	};
}
