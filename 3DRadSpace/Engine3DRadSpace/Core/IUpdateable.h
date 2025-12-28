#pragma once
#include "Libs.h"

typedef void* E3DRSP_IUpdateable;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_CORE_EXPORT void E3DRSP_IUpdateable_Update(E3DRSP_IUpdateable obj);
	E3DRSP_CORE_EXPORT void E3DRSP_IUpdateable_Destroy(E3DRSP_IUpdateable obj);
#ifdef __cplusplus
}
#endif