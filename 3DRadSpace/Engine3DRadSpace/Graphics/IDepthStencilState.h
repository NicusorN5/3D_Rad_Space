#pragma once
#include "FaceOperation.h"
#include "IGPUResource.h"
#include "DepthWriteMask.h"

typedef void* E3DRSP_IDepthStencilState;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT unsigned int E3DRSP_IDepthStencilState_StencilRef(E3DRSP_IDepthStencilState depthStencilState);
#ifdef __cplusplus
}
#endif