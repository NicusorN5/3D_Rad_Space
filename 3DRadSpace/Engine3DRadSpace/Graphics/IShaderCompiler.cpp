#include "IShaderCompiler.hpp"
#include "IShaderCompiler.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

IShaderCompiler::IShaderCompiler()
{
	_manager = std::make_unique<EffectManager>();
}

E3DRSP_CompileOutput E3DRSP_IShaderCompiler_Compile(E3DRSP_IShaderCompiler compiler, const E3DRSP_ShaderDesc desc)
{
	auto result = static_cast<IShaderCompiler*>(compiler)->Compile(reinterpret_cast<ShaderDesc*>(desc));

	E3DRSP_CompileOutput output = 
	{
		reinterpret_cast<E3DRSP_IShader*>(result.first),
		result.second.Succeded
	};
	return output;
}

E3DRSP_EffectCompileOutput E3DRSP_IShaderCompiler_CompileEffect(E3DRSP_IShaderCompiler compiler, E3DRSP_ShaderDesc* descs, size_t numDescs)
{
	auto result = static_cast<IShaderCompiler*>(compiler)->CompileEffect(std::span<ShaderDesc*>(reinterpret_cast<ShaderDesc**>(descs), numDescs));

	E3DRSP_EffectCompileOutput output =
	{
		reinterpret_cast<E3DRSP_Effect*>(result.first),
		result.second.Succeded
	};
	return output;
}

void E3DRSP_IShaderCompiler_Destroy(E3DRSP_IShaderCompiler compiler)
{
	delete static_cast<IShaderCompiler*>(compiler);
}