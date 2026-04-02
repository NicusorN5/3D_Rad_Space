#pragma once
#include "../IObject3D.h"

typedef void* E3DRSP_OBox;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT E3DRSP_OBox E3DRSP_OBox_Create();

	E3DRSP_FFI_EXPORT E3DRSP_Color E3DRSP_OBox_GetColor(E3DRSP_OBox box);
	E3DRSP_FFI_EXPORT void E3DRSP_OBox_SetColor(E3DRSP_OBox box, const E3DRSP_Color* color);
#ifdef __cplusplus
}
#endif