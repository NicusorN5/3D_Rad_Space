#pragma once
#include "../IObject3D.h"

typedef void* E3DRSP_OCylinder;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_OCylinder E3DRSP_OCylinder_Create();

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Color E3DRSP_OCylinder_GetColor(E3DRSP_OCylinder cylinder);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_OCylinder_SetColor(E3DRSP_OCylinder cylinder, const E3DRSP_Color* color);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_OCylinder_GetRadius(E3DRSP_OCylinder cylinder);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_OCylinder_SetRadius(E3DRSP_OCylinder cylinder, float radius);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_OCylinder_GetHeight(E3DRSP_OCylinder cylinder);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_OCylinder_SetHeight(E3DRSP_OCylinder cylinder, float height);

	E3DRSP_OBJECTS_IMPL_EXPORT unsigned E3DRSP_OCylinder_GetResolution(E3DRSP_OCylinder cylinder);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_OCylinder_SetResolution(E3DRSP_OCylinder cylinder, unsigned resolution);
#ifdef __cplusplus
}
#endif