#include "SourceGenerator.hpp"

extern std::unordered_map<std::string, int> file_type;

static bool generate_main_cpp(const ProjectInfo& info)
{
	std::filesystem::path main_cpp_path = info.Output / "main.cpp";

	if(std::filesystem::exists(main_cpp_path)) return true;

	std::string main =
		"#include \"MyGame.hpp\"\n"
		"#include <Windows.h>\n"
		"#include <Engine3DRadSpace\\Content\\ShaderManager.hpp>\n\n"
		"int main()\n"
		"{\n"
		"MyGame game;\n"
		"game.Run();\n\n"
		"Engine3DRadSpace::Content::ShaderManager::ReleaseAll();\n"
		"return 0;\n"
		"}\n";

	std::ofstream mainFile(main_cpp_path);
	if(!mainFile.is_open())
	{
		std::println("[FATAL] Failed to create main.cpp file.");
		return false;
	}
	mainFile << main;
	return true;
}

static bool generate_game_class(const ProjectInfo &info)
{
	std::filesystem::path game_cpp_path = info.Output /  ("Game.cpp");
	if(std::filesystem::exists(game_cpp_path)) return true;

	std::string src;

	std::ofstream gameFile(game_cpp_path);
	if(gameFile.bad() || gameFile.fail())
	{
		std::println("[ERROR] Failed to create Game.cpp file.");
		return false;
	}
	gameFile << src;

	return true;
}

std::filesystem::path CopySourceFile(
	const std::filesystem::path& completeSourceFilePath,
	const std::filesystem::path& outputDir
)
{
	std::filesystem::path filename = completeSourceFilePath.filename();

	auto existingFile = outputDir / filename;

	if(std::filesystem::exists(existingFile) && !std::filesystem::exists(completeSourceFilePath))
		return filename;

	if(completeSourceFilePath == existingFile)
		return filename;

	bool b = std::filesystem::copy_file(completeSourceFilePath, existingFile);
	if(!b)
	{
		auto strFilename = filename.string();

		std::println("[FATAL] Failed to copy file {}", strFilename);
		throw std::exception(strFilename.c_str());
	}

	return filename;
}

bool GenerateProject(const ProjectInfo &info, std::vector<std::filesystem::path> files, Compiler::Type type)
{
	if(!std::filesystem::exists(info.Output))
	{
		std::filesystem::create_directories(info.Output);
	}

	std::filesystem::path vcproj_path = info.Output / (info.Name + ".vcxproj");

	std::vector<std::filesystem::path> srcFiles;
	std::vector<std::filesystem::path> headers;
	std::vector<std::filesystem::path> resFiles;
	std::vector<std::filesystem::path> sceneFiles;

	for(auto& file : files)
	{
		switch(file_type[file.extension().string()])
		{
			case 1:
			case 3:
				srcFiles.push_back(file);
				break;
			case 2:
			case 4:
				headers.push_back(file);
				break;
			case 6:
			case 8:
				resFiles.push_back(file);
				break;
			case 7:
				sceneFiles.push_back(file);
				break;
			default:
				break;
		}
	}

	if(!generate_main_cpp(info)) return false;

	srcFiles.push_back("main.cpp");

	if(type == Compiler::Type::MSVC)
	{
		std::println("[INFO] Generating MSVC project...");

		std::string vcproj =
			"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
			"<Project DefaultTargets=\"Build\" ToolsVersion=\"17.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\n"
			"<ItemGroup Label=\"ProjectConfigurations\">\n"
			"	<ProjectConfiguration Include=\"Debug|Win64\">\n"
			"		<Configuration>Debug</Configuration>\n"
			"		<Platform>Win32</Platform>\n"
			"	</ProjectConfiguration>\n"
			"		<ProjectConfiguration Include=\"Release | Win64\">\n"
			"			<Configuration>Release</Configuration>\n"
			"			<Platform>Win32</Platform>\n"
			"		</ProjectConfiguration>\n"
			"	</ItemGroup>\n"
			"	<Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.default.props\" />\n"
			"	<PropertyGroup>\n"
			"		<ConfigurationType>Application</ConfigurationType>\n"
			"		<PlatformToolset>v143</PlatformToolset>\n"
			"	</PropertyGroup>\n"
			"	<PropertyGroup>\n"
			"		<PreferredToolArchitecture>x64</PreferredToolArchitecture>\n"
			"	</PropertyGroup>\n"
			"  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\" />\n"
			"  <ItemGroup>\n";

		for(auto& file : srcFiles)
		{
			auto filename = CopySourceFile(file, info.Output);
			vcproj += "    <ClCompile Include=\"" + filename.string() + "\" />\n";
		}

		vcproj +=	"  </ItemGroup>\n"
					"  <ItemGroup>\n";

		for(auto& file : headers)
		{
			auto filename = CopySourceFile(file, info.Output);
			vcproj += "    <ClInclude Include=\"" + filename.string() + "\" />\n";
		}

		vcproj +=	"  </ItemGroup>\n"
					"  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.Targets\" />\n"
					"</Project>\n";

		std::ofstream vcprojFile(vcproj_path);
		if(!vcprojFile.is_open())
		{
			std::println("[FATAL] Failed to create MSVC project file.");
			return false;
		}
		vcprojFile << vcproj;

		return true;
	}

	return false;
}
