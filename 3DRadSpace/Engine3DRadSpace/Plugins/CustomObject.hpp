/// ------------------------------------------------------------------------------------------------
/// File:   Plugins/CustomObject.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "../Reflection/ReflectedObject.hpp"

namespace Engine3DRadSpace::Plugins
{
	/// <summary>
	/// Returns a span of ReflectedObject references that contain custom object reflection data.
	/// </summary>
	typedef std::span<Reflection::ReflectedObject*> (*LoadCustomObjects)(void);

	/// <summary>
	/// Loads custom objects from a library handle.
	/// </summary>
	/// 
	/// <param name="libraryHandle">HMODULE in Windows</param>
	void LoadCustomObjectsFromLibHandle(void* libraryHandle);
}