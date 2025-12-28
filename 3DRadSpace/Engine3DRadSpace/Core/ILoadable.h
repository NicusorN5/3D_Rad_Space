#pragma once
#include "Libs.h"

typedef void* E3DRSP_ILoadable;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_CORE_EXPORT void E3DRSP_ILoadable_Load(E3DRSP_ILoadable obj);
	E3DRSP_CORE_EXPORT void E3DRSP_ILoadable_Load2(E3DRSP_ILoadable obj, const char* path);
	E3DRSP_CORE_EXPORT void E3DRSP_ILoadable_Destroy(E3DRSP_ILoadable obj);
#ifdef __cplusplus
}
#endif