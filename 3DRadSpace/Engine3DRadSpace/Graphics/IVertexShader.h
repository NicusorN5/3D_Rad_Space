#pragma once
#include "../Reflection/IReflectedField.h"

typedef void* E3DRSP_IVertexShader;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT Reflection::IReflectedField** E3DRSP_IVertexShader_GetInputLayout(E3DRSP_IVertexShader vertexShader, size_t *outSize);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IVertexShader_Destroy(E3DRSP_IVertexShader vertexShader);
#ifdef __cplusplus
}
#endif