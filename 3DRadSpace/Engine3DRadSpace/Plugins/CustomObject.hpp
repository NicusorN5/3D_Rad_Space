#pragma once
#include "../Reflection/ReflectedObject.hpp"

namespace Engine3DRadSpace::Plugins
{
	/// <summary>
	/// Returns a span of ReflectedObject references that contain custom object reflection data.
	/// </summary>
	typedef std::span<Reflection::ReflectedObject*> (*LoadCustomObjects)(void);

	/// <summary>
	/// Loads custom objects from a library handle for the editor.
	/// </summary>
	/// <param name="libraryHandle">HMODULE in Windows, void* in Linux</param>
	void LoadCustomObjectsFromLibHandle(void* libraryHandle);
}