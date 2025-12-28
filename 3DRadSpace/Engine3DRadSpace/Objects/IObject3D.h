#pragma once
#include "IObject.h"
#include "../Math/Ray.h"
#include "../Math/Quaternion.h"
#include "../Math/Vector3.h"

typedef void* E3DRSP_IObject3D;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_EXPORT E3DRSP_Vector3 E3DRSP_IObject3D_GetPosition(E3DRSP_IObject3D object);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_IObject3D_SetPosition(E3DRSP_IObject3D object, const E3DRSP_Vector3* pos);

	E3DRSP_OBJECTS_EXPORT E3DRSP_Vector3 E3DRSP_IObject3D_GetRotationCenter(E3DRSP_IObject3D object);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_IObject3D_SetRotationCenter(E3DRSP_IObject3D object, const E3DRSP_Vector3* center);

	E3DRSP_OBJECTS_EXPORT E3DRSP_Quaternion E3DRSP_IObject3D_GetRotation(E3DRSP_IObject3D object);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_IObject3D_SetRotation(E3DRSP_IObject3D object, const E3DRSP_Quaternion* rotation);

	E3DRSP_OBJECTS_EXPORT E3DRSP_Vector3 E3DRSP_IObject3D_GetScale(E3DRSP_IObject3D object);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_IObject3D_SetScale(E3DRSP_IObject3D object, const E3DRSP_Vector3* scale);

	E3DRSP_OBJECTS_EXPORT E3DRSP_Matrix4x4 E3DRSP_IObject3D_GetModelMatrix(E3DRSP_IObject3D object);
	E3DRSP_OBJECTS_EXPORT float* E3DRSP_IObject3D_Intersects(E3DRSP_IObject3D object, const E3DRSP_Ray* ray);
#ifdef __cplusplus
}
#endif