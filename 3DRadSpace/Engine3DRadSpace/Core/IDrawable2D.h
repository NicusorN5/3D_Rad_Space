#pragma once
#include "../Core/Libs.h"

typedef void* E3DRSP_IDrawable2D;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_CORE_EXPORT void E3DRSP_IDrawable2D_Draw2D(E3DRSP_IDrawable2D drawable);
	E3DRSP_CORE_EXPORT void E3DRSP_IDrawable2D_Destroy(E3DRSP_IDrawable2D drawable);
#ifdef __cplusplus
}
#endif