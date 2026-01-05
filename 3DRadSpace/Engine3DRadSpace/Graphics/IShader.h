#pragma once
#include "ShaderFeatureLevel.h"
#include "IGPUResource.h"
#include "../Reflection/IReflectedField.h"

typedef void* E3DRSP_ITexture2D;
typedef void* E3DRSP_ISamplerState;

typedef void* E3DRSP_IShader;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IShader_SetData(E3DRSP_IShader shader, unsigned index, const void *data, size_t dataSize);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IShader_SetTexture(E3DRSP_IShader shader, unsigned index, E3DRSP_ITexture2D texture);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IShader_SetTextures(E3DRSP_IShader shader, E3DRSP_ITexture2D* textures, size_t numTextures);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IShader_SetSampler(E3DRSP_IShader shader, unsigned index, E3DRSP_ISamplerState samplerState) ;
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IShader_SetShader(E3DRSP_IShader shader);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IReflectedField* E3DRSP_IShader_GetVariables(E3DRSP_IShader shader, size_t *outSize);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IShader_Set(E3DRSP_IShader shader, const char* name, const void* data, size_t dataSize);

	E3DRSP_GRAPHICS_EXPORT const char* E3DRSP_IShader_GetEntryName(E3DRSP_IShader shader);
	E3DRSP_GRAPHICS_EXPORT const char* E3DRSP_IShader_GetCompilationErrorsAndWarnings(E3DRSP_IShader shader);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IShader_Destroy(E3DRSP_IShader shader);
#ifdef __cplusplus
}
#endif