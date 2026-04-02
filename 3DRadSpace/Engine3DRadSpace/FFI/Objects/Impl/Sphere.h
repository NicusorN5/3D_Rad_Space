#pragma once
#include "../IObject3D.h"

typedef void* E3DRSP_OSphere;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_OSphere E3DRSP_OSphere_Create();

	E3DRSP_FFI_EXPORT E3DRSP_Color E3DRSP_OSphere_GetColor(E3DRSP_OSphere sphere);
	E3DRSP_FFI_EXPORT void E3DRSP_OSphere_SetColor(E3DRSP_OSphere sphere, const E3DRSP_Color* color);

	E3DRSP_FFI_EXPORT float E3DRSP_OSphere_GetRadius(E3DRSP_OSphere sphere);
	E3DRSP_FFI_EXPORT void E3DRSP_OSphere_SetRadius(E3DRSP_OSphere sphere, float radius);

	E3DRSP_FFI_EXPORT unsigned E3DRSP_OSphere_GetResolution(E3DRSP_OSphere sphere);
	E3DRSP_FFI_EXPORT void E3DRSP_OSphere_SetResolution(E3DRSP_OSphere sphere, unsigned resolution);
#ifdef __cplusplus
}
#endif