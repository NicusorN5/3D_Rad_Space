#pragma once
#include "../IObject3D.h"

typedef void* E3DRSP_OCone;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_OCone E3DRSP_OCone_Create();

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Color E3DRSP_OCone_GetColor(E3DRSP_OCone cone);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_OCone_SetColor(E3DRSP_OCone cone, const E3DRSP_Color* color);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_OCone_GetRadius(E3DRSP_OCone cone);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_OCone_SetRadius(E3DRSP_OCone cone, float radius);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_OCone_GetHeight(E3DRSP_OCone cone);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_OCone_SetHeight(E3DRSP_OCone cone, float height);

	E3DRSP_OBJECTS_IMPL_EXPORT unsigned E3DRSP_OCone_GetResolution(E3DRSP_OCone cone);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_OCone_SetResolution(E3DRSP_OCone cone, unsigned resolution);
#ifdef __cplusplus
}
#endif