#pragma once
#include "../IObject3D.h"

typedef void* E3DRSP_Skinmesh;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_Skinmesh E3DRSP_Skinmesh_Create();

	E3DRSP_FFI_EXPORT unsigned E3DRSP_Skinmesh_GetModel(E3DRSP_Skinmesh skinmesh);
	E3DRSP_FFI_EXPORT void E3DRSP_Skinmesh_SetModel(E3DRSP_Skinmesh skinmesh, unsigned modelID);
#ifdef __cplusplus
}
#endif