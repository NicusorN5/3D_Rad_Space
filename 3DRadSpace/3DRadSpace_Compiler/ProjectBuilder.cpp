#include "ProjectBuilder.hpp"

bool MSVC_Build(const ProjectInfo& project, const std::filesystem::path& compilerPath)
{
	auto projectPath = project.Output / (project.Name + ".vcxproj");
	std::string command = "\"\"" + compilerPath.string() + "\" \"" + (std::filesystem::canonical(projectPath).string()) + "\" /Build Release\"";

	int r = std::system(command.c_str());
	return r;
}

bool Clang_Build(const ProjectInfo& project, const std::filesystem::path& compilerPath)
{
	return false;
}

bool GCC_Build(const ProjectInfo& project, const std::filesystem::path& compilerPath)
{
	return false;
}
