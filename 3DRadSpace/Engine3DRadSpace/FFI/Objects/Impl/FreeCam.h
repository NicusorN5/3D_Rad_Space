#pragma once
#include "Camera.h"
#include "../../Input/Key.h"

typedef void* E3DRSP_FreeCam;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_FreeCam E3DRSP_FreeCam_Create();

	E3DRSP_FFI_EXPORT float E3DRSP_FreeCam_GetMovementSpeed(E3DRSP_FreeCam freecam);
	E3DRSP_FFI_EXPORT void E3DRSP_FreeCam_SetMovementSpeed(E3DRSP_FreeCam freecam, float speed);

	E3DRSP_FFI_EXPORT bool E3DRSP_FreeCam_IsXInverted(E3DRSP_FreeCam freecam);
	E3DRSP_FFI_EXPORT void E3DRSP_FreeCam_SetXInverted(E3DRSP_FreeCam freecam, bool invertX);

	E3DRSP_FFI_EXPORT bool E3DRSP_FreeCam_IsYInverted(E3DRSP_FreeCam freecam);
	E3DRSP_FFI_EXPORT void E3DRSP_FreeCam_SetYInverted(E3DRSP_FreeCam freecam, bool invertX);

	E3DRSP_FFI_EXPORT E3DRSP_Key E3DRSP_FreeCam_GetForwardKey(E3DRSP_FreeCam freecam);
	E3DRSP_FFI_EXPORT void E3DRSP_FreeCam_SetForwardKey(E3DRSP_FreeCam freecam, E3DRSP_Key key);

	E3DRSP_FFI_EXPORT E3DRSP_Key E3DRSP_FreeCam_GetBackwardKey(E3DRSP_FreeCam freecam);
	E3DRSP_FFI_EXPORT void E3DRSP_FreeCam_SetBackwardKey(E3DRSP_FreeCam freecam, E3DRSP_Key key);

	E3DRSP_FFI_EXPORT E3DRSP_Key E3DRSP_FreeCam_GetLeftKey(E3DRSP_FreeCam freecam);
	E3DRSP_FFI_EXPORT void E3DRSP_FreeCam_SetLeftKey(E3DRSP_FreeCam freecam, E3DRSP_Key key);

	E3DRSP_FFI_EXPORT E3DRSP_Key E3DRSP_FreeCam_GetRightKey(E3DRSP_FreeCam freecam);
	E3DRSP_FFI_EXPORT void E3DRSP_FreeCam_SetRightKey(E3DRSP_FreeCam freecam, E3DRSP_Key key);
#ifdef __cplusplus
}
#endif