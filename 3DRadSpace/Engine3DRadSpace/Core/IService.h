#pragma once
#include "Libs.h"

typedef void* E3DRSP_IService;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_CORE_EXPORT void E3DRSP_IService_Destroy(E3DRSP_IService* service);
#ifdef __cplusplus
}
#endif