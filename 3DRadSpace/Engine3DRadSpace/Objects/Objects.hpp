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
	void E3DRSP_OBJECTS_EXPORT LoadDefaultObjects();
	Reflection::ReflectedObject E3DRSP_OBJECTS_EXPORT *GetReflDataFromUUID(const Reflection::UUID &uuid);
}

extern E3DRSP_OBJECTS_EXPORT std::vector<Engine3DRadSpace::Reflection::ReflectedObject*> _3drsp_internal_objects_list;