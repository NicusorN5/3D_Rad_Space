#include "CppScriptBuilder.hpp"

using namespace Engine3DRadSpace::Scripting;
using namespace Engine3DRadSpace::Scripting::CPP;

CppScriptBuilder::CppScriptBuilder()
{

}

const std::string CppScriptBuilder::Language() const
{
	return "C++";
}

IScriptBuilder::CompileReturn CppScriptBuilder::Compile(const std::filesystem::path& scriptPath)
{
	if(!std::filesystem::exists(scriptPath))
		return std::make_pair<IScriptInstance, CompilationResults>(
			nullptr,
			CompilationResults
			{
				.Successful = false,
				.Errors = std::format("Source file not found {}", scriptPath.string()),
				.Warnings = "",
				.Messages = "",
			});

	//TODO: Invoke compiler:

	return { nullptr, CompilationResults{false,"",""} };
}

bool CppScriptBuilder::IsAvailable() const
{
	return true;
}
