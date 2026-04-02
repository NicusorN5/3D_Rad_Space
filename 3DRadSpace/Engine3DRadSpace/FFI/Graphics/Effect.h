#pragma once
#include "IGraphicsDevice.h"
#include "IShader.h"
#include "ShaderType.h"

typedef void* E3DRSP_E3DRSP_ITexture2D;
typedef void* E3DRSP_ISamplerState;
/// <summary>
/// Represents references to N shaders, all making up a pipeline.
/// </summary>
typedef void* E3DRSP_Effect;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT E3DRSP_Effect E3DRSP_Effect_Create(E3DRSP_IGraphicsDevice device, E3DRSP_IShader* shaders, size_t numShaders);

	E3DRSP_GRAPHICS_EXPORT int E3DRSP_Effect_SetAll(E3DRSP_Effect effect);
	E3DRSP_GRAPHICS_EXPORT bool E3DRSP_Effect_Set(E3DRSP_Effect effect, int index);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_Effect_SetData(E3DRSP_Effect effect, void* data, size_t size, int cbufferID, int shaderID);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_Effect_SetData2(E3DRSP_Effect effect, void* data, size_t size, int cbufferID);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_Effect_SetTexture(E3DRSP_Effect effect, E3DRSP_ITexture2D texture, int idx);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_Effect_SetTexture2(E3DRSP_Effect effect, E3DRSP_ITexture2D texture, int textureID, int shaderID);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_Effect_SetSampler(E3DRSP_Effect effect, E3DRSP_ISamplerState sampler, int idx);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_Effect_SetSampler2(E3DRSP_Effect effect, E3DRSP_ISamplerState sampler, int samplerID, int shaderID);

	E3DRSP_GRAPHICS_EXPORT E3DRSP_IShader* E3DRSP_Effect_GetShader(E3DRSP_Effect effect, size_t idx);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_Effect_Destroy(E3DRSP_Effect effect);
#ifdef __cplusplus
}
#endif