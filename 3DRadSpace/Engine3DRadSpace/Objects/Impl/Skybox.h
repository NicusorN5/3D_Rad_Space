#pragma once
#include "../IObject3D.h"

typedef void* E3DRSP_Skybox;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Skybox E3DRSP_Skybox_Create();

	E3DRSP_OBJECTS_IMPL_EXPORT unsigned E3DRSP_Skybox_Get(E3DRSP_Skybox skybox);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Skybox_Set(E3DRSP_Skybox skybox, unsigned skyboxID);
#ifdef __cplusplus
}
#endif