#pragma once
#include "../IObject.h"

typedef void* E3DRSP_Fog;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Fog E3DRSP_Fog_Create();

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_Fog_GetFogBegin(E3DRSP_Fog fog);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Fog_SetFogBegin(E3DRSP_Fog fog, float fogBegin);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_Fog_GetFogEnd(E3DRSP_Fog fog);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Fog_SetFogEnd(E3DRSP_Fog fog, float fogEnd);

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Color E3DRSP_Fog_GetFogColor(E3DRSP_Fog fog);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Fog_SetFogColor(E3DRSP_Fog fog, const E3DRSP_Color *fogCplor);
#ifdef __cplusplus
}
#endif