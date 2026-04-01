#pragma once
#include "IObject.h"

typedef void* E3DRSP_ObjectCollection;

#ifdef __cplusplus
extern "C" {
#endif
	E3DRSP_OBJECTS_EXPORT E3DRSP_ObjectCollection E3DRSP_ObjectCollection_Create();
	E3DRSP_OBJECTS_EXPORT void E3DRSP_ObjectCollection_Add(E3DRSP_ObjectCollection collection, E3DRSP_IObject object);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_ObjectCollection_Remove(E3DRSP_ObjectCollection collection, E3DRSP_IObject object);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_ObjectCollection_RemoveID(E3DRSP_ObjectCollection collection, size_t index);
	E3DRSP_OBJECTS_EXPORT E3DRSP_IObject E3DRSP_ObjectCollection_At(E3DRSP_ObjectCollection collection, size_t index);
	E3DRSP_OBJECTS_EXPORT size_t E3DRSP_ObjectCollection_Count(E3DRSP_ObjectCollection collection);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_ObjectCollection_Clear(E3DRSP_ObjectCollection collection);
#ifdef __cplusplus
}
#endif