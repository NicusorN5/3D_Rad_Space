#pragma once
#include "../Core/Libs.h"
#include "ShaderType.h"
#include "ShaderFeatureLevel.h"

typedef void* E3DRSP_ShaderDesc;

#ifdef __cplusplus
extern "C"
{
#endif
E3DRSP_GRAPHICS_EXPORT E3DRSP_ShaderDesc E3DRSP_ShaderDesc_CreateFromFile(
	const char* filePath,
	const char* entryPoint,
	E3DRSP_ShaderType type,
	E3DRSP_ShaderFeatureLevel featureLevel
);

E3DRSP_GRAPHICS_EXPORT E3DRSP_ShaderDesc E3DRSP_ShaderDesc_CreateFromSource(
	const char* sourceCode,
	const char* entryPoint,
	E3DRSP_ShaderType type,
	E3DRSP_ShaderFeatureLevel featureLevel
);

E3DRSP_GRAPHICS_EXPORT void E3DRSP_ShaderDesc_Destroy(E3DRSP_ShaderDesc shaderDesc);

#ifdef __cplusplus
}
#endif