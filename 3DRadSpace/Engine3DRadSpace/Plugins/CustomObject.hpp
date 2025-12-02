#pragma once
#include "../Reflection/ReflectedObject.hpp"
#include "../Core/RawSpan.h"

namespace Engine3DRadSpace::Plugins
{
	/// <summary>
	/// Returns a span of ReflectedObject references that contain custom object reflection data.
	/// </summary>
	typedef E3DRSP_RawSpan (*LoadCustomObjects)(void);

	/// <summary>
	/// Loads custom objects from a library handle for the editor.
	/// </summary>
	/// <param name="libraryHandle">HMODULE in Windows, void* in Linux</param>
	void E3DRSP_PLUGINS_EXPORT LoadCustomObjectsFromLibHandle(void* libraryHandle);
}