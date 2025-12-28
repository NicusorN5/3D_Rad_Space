#pragma once
#include "../Core/Libs.h"

typedef void* E3DRSP_IRasterizerState;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IRasterizerState_Destroy(E3DRSP_IRasterizerState rasterizerState);
#ifdef __cplusplus
}
#endif