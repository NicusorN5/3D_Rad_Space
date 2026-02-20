#pragma once
#include "../IObject3D.h"

typedef void* E3DRSP_Camera;

enum E3DRSP_Camera_LookMode
{
	E3DRSP_Camera_LookMode_UseRotation,
	E3DRSP_Camera_LookMode_UseLookatCoordinates
};

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Camera E3DRSP_Camera_Create();

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Vector3 E3DRSP_Camera_GetNormal(E3DRSP_Camera camera);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetNormal(E3DRSP_Camera camera, const E3DRSP_Vector3* vector);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_Camera_GetAspectRatio(E3DRSP_Camera camera);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetAspectRatio(E3DRSP_Camera camera, float aspectRatio);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_Camera_GetFOV(E3DRSP_Camera camera);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetFOV(E3DRSP_Camera camera, float fov);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_Camera_GetNPD(E3DRSP_Camera camera);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetNPD(E3DRSP_Camera camera, float nearPlaneDistance);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_Camera_GetFPD(E3DRSP_Camera camera);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetFPD(E3DRSP_Camera camera, float farPlaneDistance);

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Camera_LookMode E3DRSP_Camera_GetLookMode(E3DRSP_Camera camera);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetLookMode(E3DRSP_Camera camera, E3DRSP_Camera_LookMode lookMode);

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Vector3 E3DRSP_Camera_GetLookAt(E3DRSP_Camera camera);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetLookAt(E3DRSP_Camera camera, const E3DRSP_Vector3* vector);

#ifdef __cplusplus
}
#endif