#pragma once
#include "../IObject2D.h"

typedef void* E3DRSP_ExitFade;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_ExitFade E3DRSP_ExitFade_Create();

	E3DRSP_OBJECTS_IMPL_EXPORT const char* E3DRSP_Camera_GetProjectPath(E3DRSP_ExitFade exitFade);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetProjectPath(E3DRSP_ExitFade exitFade, const char* path);

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Color E3DRSP_Camera_GetFadeColor(E3DRSP_ExitFade exitFade);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetFadeColor(E3DRSP_ExitFade exitFade, const E3DRSP_Color* color);

	E3DRSP_OBJECTS_IMPL_EXPORT float E3DRSP_Camera_GetFadeTime(E3DRSP_ExitFade exitFade);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Camera_SetFadeTime(E3DRSP_ExitFade exitFade, float timeMs);
#ifdef __cplusplus
}
#endif