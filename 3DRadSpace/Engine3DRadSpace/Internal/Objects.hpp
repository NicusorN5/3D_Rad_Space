/// ------------------------------------------------------------------------------------------------
/// File:   Internal/Objects.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "../Reflection/ReflectedObject.hpp"

/// ------------------------------------------------------------------------------------------------
///
///					!!NOTICE!!
/// 
///		This is not meant to be used by the user, but by the engine itself.
///		This header only contains a forward reference to a function that loads the default 3DRadSpace objects (Skinmesh, Camera, etc).
/// 
/// ------------------------------------------------------------------------------------------------

namespace Engine3DRadSpace::Internal
{
	void DLLEXPORT LoadDefaultObjects();
	Reflection::ReflectedObject DLLEXPORT *GetReflDataFromUUID(const Reflection::UUID &uuid);
}

extern DLLEXPORT std::vector<Engine3DRadSpace::Reflection::ReflectedObject*> _3drsp_internal_objects_list;