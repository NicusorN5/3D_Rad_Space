#pragma once
#include "../Math/Matrix4x4.h"

typedef void* E3DRSP_ICamera;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_EXPORT E3DRSP_Matrix4x4 E3DRSP_ICamera_GetViewMatrix(E3DRSP_ICamera cam);
	E3DRSP_OBJECTS_EXPORT E3DRSP_Matrix4x4 E3DRSP_ICamera_GetProjectionMatrix(E3DRSP_ICamera cam);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_ICamera_Destroy(E3DRSP_ICamera cam);
#ifdef __cplusplus
}
#endif