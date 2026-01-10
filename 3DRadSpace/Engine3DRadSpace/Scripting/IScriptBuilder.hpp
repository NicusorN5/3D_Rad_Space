#pragma once
#include "IScript.hpp"
#include "CompilationResults.hpp"

namespace Engine3DRadSpace::Scripting
{
	class E3DRSP_SCRIPTING_EXPORT IScriptBuilder
	{
	protected:
		IScriptBuilder() = default;
	public:
		virtual const char* Language() const = 0;
		virtual bool IsAvailable() const = 0;

		using CompileReturn = std::pair<IScript*, CompilationResults>;
		virtual CompileReturn Compile(const char* scriptPath, const char* entryClass) = 0;

		virtual ~IScriptBuilder() = default;
	};
}