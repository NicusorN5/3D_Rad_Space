#pragma once
#include "IObject.h"
#include "../Math/Vector2.h"

typedef void* E3DRSP_IObject2D;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_EXPORT E3DRSP_Vector2 E3DRSP_IObject2D_GetPosition(E3DRSP_IObject2D object);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_IObject2D_SetPosition(E3DRSP_IObject2D object, const E3DRSP_Vector2* pos);

	E3DRSP_OBJECTS_EXPORT E3DRSP_Vector2 E3DRSP_IObject2D_GetRotationCenter(E3DRSP_IObject2D object);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_IObject2D_SetRotationCenter(E3DRSP_IObject2D object, const E3DRSP_Vector2* center);

	E3DRSP_OBJECTS_EXPORT float E3DRSP_IObject2D_GetRotation(E3DRSP_IObject2D object);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_IObject2D_SetRotation(E3DRSP_IObject2D object, float rotation);

	E3DRSP_OBJECTS_EXPORT E3DRSP_Vector2 E3DRSP_IObject2D_GetScale(E3DRSP_IObject2D object);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_IObject2D_SetScale(E3DRSP_IObject2D object, const E3DRSP_Vector2* scale);

	E3DRSP_OBJECTS_EXPORT float E3DRSP_IObject2D_GetDepth(E3DRSP_IObject2D object);
	E3DRSP_OBJECTS_EXPORT void E3DRSP_IObject2D_SetDepth(E3DRSP_IObject2D object, float depth);
#ifdef __cplusplus
}
#endif