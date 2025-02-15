/// ------------------------------------------------------------------------------------------------
/// File:   IObject2D.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "IObject2D.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;

IObject2D::IObject2D(const std::string &name, bool enabled, bool visible, const Vector2&pos, const
                     Vector2&scale, 
                     float rotation, const Vector2&pivot, float depth) :
	IObject(name, false, false),
	Position(pos),
	Rotation(rotation),
	RotationCenter(pivot),
	Scale(scale),
	Depth(depth)
{
}
