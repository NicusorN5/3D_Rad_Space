#include "ProjectBuilder.hpp"

void MSVC_Build(const ProjectInfo& project, const std::filesystem::path& compilerPath)
{
	auto projectPath = project.Output / (project.Name + ".vcproj");

	std::string command = "\"\"" + compilerPath.string() + "\" \"" + projectPath.string() + "\" /Build\"";

	int r = std::system(command.c_str());
	if(r != 0)
	{
		std::println("[ERROR] Failed to build project with MSVC.");
	}
	else
	{
		std::println("[SUCCESS]Finished building.");
	}
}

void Clang_Build(const ProjectInfo& project, const std::filesystem::path& compilerPath)
{

}

void GCC_Build(const ProjectInfo& project, const std::filesystem::path& compilerPath)
{

}
