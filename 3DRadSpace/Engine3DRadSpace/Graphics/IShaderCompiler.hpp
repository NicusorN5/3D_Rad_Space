#pragma once
#include "ShaderCompilationResult.hpp"
#include "ShaderDesc.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Effect;

	class E3DRSP_GRAPHICS_EXPORT IShaderCompiler
	{
	protected:
		IShaderCompiler() = default;
	public:
		using CompileOutput = std::pair<std::unique_ptr<IShader>, ShaderCompilationResult>;
		using EffectCompileOutput = std::pair<std::unique_ptr<Effect>, ShaderCompilationResult>;

		virtual CompileOutput Compile(const ShaderDesc* desc) = 0;
		virtual std::vector<EffectCompileOutput> CompileEffect(const ShaderDesc* const* descs) = 0;

		virtual ~IShaderCompiler() = default;
	};
}