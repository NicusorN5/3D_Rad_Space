#pragma once
#include "../IObject.h"

typedef void* E3DRSP_Counter;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Counter E3DRSP_Counter_Create();

	E3DRSP_OBJECTS_IMPL_EXPORT double E3DRSP_Camera_GetValue(E3DRSP_Counter counter);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetValue(E3DRSP_Counter counter, double value);

	E3DRSP_OBJECTS_IMPL_EXPORT double E3DRSP_Camera_GetIncrement(E3DRSP_Counter counter);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetIncrement(E3DRSP_Counter counter, double value);

	E3DRSP_OBJECTS_IMPL_EXPORT bool E3DRSP_Camera_IsLoadingFromFile(E3DRSP_Counter counter);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetLoadingFromFile(E3DRSP_Counter counter, bool value);

	E3DRSP_OBJECTS_IMPL_EXPORT const char* E3DRSP_Camera_GetFile(E3DRSP_Counter counter);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetFile(E3DRSP_Counter counter, const char* path);

	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_Save(E3DRSP_Counter counter);
#ifdef __cplusplus
}
#endif