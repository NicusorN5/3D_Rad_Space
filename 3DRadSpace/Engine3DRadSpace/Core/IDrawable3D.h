#pragma once
#include "../Core/Libs.h"

typedef void* E3DRSP_IDrawable3D;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_CORE_EXPORT void E3DRSP_IDrawable3D_Draw3D(E3DRSP_IDrawable3D drawable);
	E3DRSP_CORE_EXPORT void E3DRSP_IDrawable3D_Destroy(E3DRSP_IDrawable3D drawable);
#ifdef __cplusplus
}
#endif