#pragma once
#include "ShaderCompilationResult.h"
#include "ShaderDesc.h"
#include "EffectManager.h"

typedef void* E3DRSP_IShader;
typedef void* E3DRSP_Effect;
typedef void* E3DRSP_IShaderCompiler;

struct E3DRSP_CompileOutput
{
	E3DRSP_IShader* shader;
	E3DRSP_ShaderCompilationResult result;
};

struct E3DRSP_EffectCompileOutput
{
	E3DRSP_Effect* effect;
	E3DRSP_ShaderCompilationResult result;
};

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT E3DRSP_CompileOutput E3DRSP_IShaderCompiler_Compile(E3DRSP_IShaderCompiler compiler, const E3DRSP_ShaderDesc desc);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_EffectCompileOutput E3DRSP_IShaderCompiler_CompileEffect(E3DRSP_IShaderCompiler compiler, E3DRSP_ShaderDesc* descs, size_t numDescs);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_IShaderCompiler_Destroy(E3DRSP_IShaderCompiler compiler);
#ifdef __cplusplus
}
#endif