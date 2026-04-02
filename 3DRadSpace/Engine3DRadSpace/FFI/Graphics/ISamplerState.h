#pragma once
#include "../../Core/Libs.hpp"

typedef void* E3DRSP_ISamplerState;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_FFI_EXPORT void E3DRSP_ISamplerState_Destroy(E3DRSP_ISamplerState samplerState);
#ifdef __cplusplus
}
#endif