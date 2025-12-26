#pragma once
#include "IReflectedField.h"
#include "UUID.h"

typedef void* E3DRSP_ReflectedObject;

#ifdef __cplusplus
extern "C" {
#endif
	E3DRSP_REFLECTION_EXPORT E3DRSP_ReflectedObject E3DRSP_ReflectedObject_Create(
		const char* name,
		const char* category,
		const char* description,
		const E3DRSP_IReflectedField* fields,
		size_t numFields,
		const E3DRSP_UUID* objectUUID
	);

	E3DRSP_REFLECTION_EXPORT const char* E3DRSP_ReflectedObject_GetName(E3DRSP_ReflectedObject obj);
	E3DRSP_REFLECTION_EXPORT const char* E3DRSP_ReflectedObject_GetCategory(E3DRSP_ReflectedObject obj);
	E3DRSP_REFLECTION_EXPORT const char* E3DRSP_ReflectedObject_GetDescription(E3DRSP_ReflectedObject obj);
	E3DRSP_REFLECTION_EXPORT E3DRSP_UUID E3DRSP_ReflectedObject_GetUUID(E3DRSP_ReflectedObject obj);
	E3DRSP_REFLECTION_EXPORT size_t E3DRSP_ReflectedObject_GetNumFields(E3DRSP_ReflectedObject obj);
	E3DRSP_REFLECTION_EXPORT const E3DRSP_IReflectedField E3DRSP_ReflectedObject_GetFieldByIndex(E3DRSP_ReflectedObject obj, size_t index);
	E3DRSP_REFLECTION_EXPORT const E3DRSP_IReflectedField E3DRSP_ReflectedObject_GetFieldByName(E3DRSP_ReflectedObject obj, const char* name);
	E3DRSP_REFLECTION_EXPORT void* E3DRSP_ReflectedObject_CreateBlankObject(E3DRSP_ReflectedObject obj);

	E3DRSP_REFLECTION_EXPORT void E3DRSP_ReflectedObject_Destroy(E3DRSP_ReflectedObject obj);
#ifdef __cplusplus
}
#endif