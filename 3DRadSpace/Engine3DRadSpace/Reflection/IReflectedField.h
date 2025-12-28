#pragma once
#include "FieldRepresentation.hpp"

typedef void* E3DRSP_IReflectedField;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_REFLECTION_EXPORT const size_t E3DRSP_IReflectedField_TypeHash(E3DRSP_IReflectedField field);
	E3DRSP_REFLECTION_EXPORT const char* E3DRSP_IReflectedField_FieldName(E3DRSP_IReflectedField field);
	E3DRSP_REFLECTION_EXPORT const char* E3DRSP_IReflectedField_FieldDesc(E3DRSP_IReflectedField field);
	E3DRSP_REFLECTION_EXPORT const size_t E3DRSP_IReflectedField_TypeSize(E3DRSP_IReflectedField field);
	E3DRSP_REFLECTION_EXPORT const ptrdiff_t E3DRSP_IReflectedField_FieldOffset(E3DRSP_IReflectedField field);

	E3DRSP_REFLECTION_EXPORT const void* E3DRSP_IReflectedField_Get(E3DRSP_IReflectedField field, void* objPtr);
	E3DRSP_REFLECTION_EXPORT void E3DRSP_IReflectedField_Set(E3DRSP_IReflectedField field, void* objPtr, const void* value);

	E3DRSP_REFLECTION_EXPORT const void* E3DRSP_IReflectedField_DefaultValue(E3DRSP_IReflectedField field);

	E3DRSP_REFLECTION_EXPORT void E3DRSP_IReflectedField_Destroy(E3DRSP_IReflectedField field);
#ifdef __cplusplus
}
#endif