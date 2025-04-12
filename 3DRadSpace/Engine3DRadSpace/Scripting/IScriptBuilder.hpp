#pragma once
#include "IScript.hpp"
#include "CompilationResults.hpp"

namespace Engine3DRadSpace::Scripting
{
	class DLLEXPORT IScriptBuilder
	{
	protected:
		IScriptBuilder() = default;
	public:
		virtual const std::string Language() const = 0;
		virtual bool IsAvailable() const = 0;

		using CompileReturn = std::pair<IScriptInstance, CompilationResults>;
		virtual CompileReturn Compile(const std::filesystem::path& scriptPath) = 0;

		virtual ~IScriptBuilder() = default;
	};
}