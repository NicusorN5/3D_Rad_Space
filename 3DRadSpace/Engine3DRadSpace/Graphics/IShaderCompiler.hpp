#pragma once
#include "ShaderCompilationResult.hpp"
#include "ShaderDesc.hpp"
#include "EffectManager.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Effect;
	class IShader;

	class E3DRSP_GRAPHICS_EXPORT IShaderCompiler
	{
	protected:
		IShaderCompiler();

		std::unique_ptr<EffectManager> _manager;
	public:
		using CompileOutput = std::pair<IShader*, ShaderCompilationResult>;
		using EffectCompileOutput = std::pair<Effect*, ShaderCompilationResult>;

		virtual [[nodiscard]] CompileOutput Compile(const ShaderDesc* desc) = 0;
		virtual [[nodiscard]] EffectCompileOutput CompileEffect(std::span<ShaderDesc*> descs) = 0;

		virtual ~IShaderCompiler() = default;
	};
}