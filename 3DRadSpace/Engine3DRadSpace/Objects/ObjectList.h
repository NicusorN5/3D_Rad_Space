#pragma once
#include "IObject.h"
#include "../Reflection/ReflectedObject.h"
#include "../Core/IGame.h"

typedef void* E3DRSP_ObjectList;

#ifdef __cplusplus
extern "C" 
{
#endif
	E3DRSP_OBJECTS_EXPORT E3DRSP_ObjectList E3DRSP_ObjectList_Create(E3DRSP_IGame game);
	E3DRSP_OBJECTS_EXPORT unsigned E3DRSP_ObjectList_Add(E3DRSP_ObjectList list, E3DRSP_IObject obj);
	E3DRSP_OBJECTS_EXPORT E3DRSP_IObject E3DRSP_ObjectList_FindByID(E3DRSP_ObjectList list, unsigned id);
	E3DRSP_OBJECTS_EXPORT E3DRSP_IObject E3DRSP_ObjectList_FindByName(E3DRSP_ObjectList list, const char* name);

	E3DRSP_OBJECTS_EXPORT void E3DRSP_ObjectList_RemoveByID(E3DRSP_ObjectList list, unsigned id);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_ObjectList_RemoveByName(E3DRSP_ObjectList list, const char* name);
#ifdef __cplusplus
}
#endif
