#pragma once
#include "ShaderCompilationResult.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IShaderCompiler
	{
	protected:
		IShaderCompiler() = default;
	public:
		virtual ShaderCompilationResult CompileFile(const std::filesystem::path& path, const std::string& entryPoint) = 0;
		virtual ShaderCompilationResult Compile(const std::string& src, const std::string& entryPoint) = 0;

		virtual ~IShaderCompiler() = default;
	}
}