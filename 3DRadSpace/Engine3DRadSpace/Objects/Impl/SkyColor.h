#pragma once
#include "../IObject.h"

typedef void* E3DRSP_SkyColor;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_SkyColor E3DRSP_SkyColor_Create();

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Color E3DRSP_SkyColor_Get(E3DRSP_SkyColor skyColor);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_SkyColor_Set(E3DRSP_SkyColor skyColor, const E3DRSP_Color* color);
#ifdef __cplusplus
}
#endif