#include "CppScriptBuilder.hpp"

using namespace Engine3DRadSpace::Scripting;
using namespace Engine3DRadSpace::Scripting::CPP;

CppScriptBuilder::CppScriptBuilder()
{

}

const char* CppScriptBuilder::Language() const
{
	return "C++";
}

IScriptBuilder::CompileReturn CppScriptBuilder::Compile(const char* scriptPath, const char* entryClass)
{
	if(!std::filesystem::exists(scriptPath))
		return std::make_pair<IScript*, CompilationResults>(
			nullptr,
			CompilationResults
			{
				.Successful = false,
				.Errors = "Source file not found",
				.Warnings = "",
				.Messages = scriptPath,
			});

	//TODO: Invoke compiler:

	return { nullptr, CompilationResults{false,"",""} };
}

bool CppScriptBuilder::IsAvailable() const
{
	return true;
}
