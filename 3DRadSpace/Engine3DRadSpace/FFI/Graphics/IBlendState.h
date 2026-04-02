#pragma once
#include "../Math/Color.h"

typedef void* E3DRSP_IBlendState;

#ifdef __cplusplus
extern "C"
{
#endif
    E3DRSP_FFI_EXPORT E3DRSP_Color E3DRSP_IBlendState_BlendFactor(E3DRSP_IBlendState blendState);
    E3DRSP_FFI_EXPORT unsigned int E3DRSP_IBlendState_SampleMask(E3DRSP_IBlendState blendState);
    E3DRSP_FFI_EXPORT void E3DRSP_IBlendState_Destroy(E3DRSP_IBlendState blendState);
#ifdef __cplusplus
}
#endif
