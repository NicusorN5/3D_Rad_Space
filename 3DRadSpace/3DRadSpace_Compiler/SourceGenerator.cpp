#include "SourceGenerator.hpp"

extern std::unordered_map<std::string, int> file_type;

static bool generate_main_cpp(const ProjectInfo& info)
{
	std::filesystem::path main_cpp_path = info.Output / "main.cpp";

	if(std::filesystem::exists(main_cpp_path)) return true;

	std::string main =
		"#include \"MyGame.hpp\"\r\n"
		"#include <Windows.h>\r\n"
		"#include <Engine3DRadSpace\\Content\\ShaderManager.hpp>\r\n\r\n"
		"int main()\r\n"
		"{\r\n"
		"MyGame game;\r\n"
		"game.Run();\r\n\r\n"
		"Engine3DRadSpace::Content::ShaderManager::ReleaseAll();\r\n"
		"return 0;\r\n"
		"}\r\n";

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

bool GenerateProject(const ProjectInfo &info, std::vector<std::filesystem::path> files, Compiler::Type type)
{
	if(!std::filesystem::exists(info.Output))
	{
		std::filesystem::create_directories(info.Output);
	}

	std::filesystem::path vcproj_path = info.Output / (info.Name + ".vcxproj");

	//Assume project was already generated.
	if(std::filesystem::exists(vcproj_path)) return true;

	std::vector<std::filesystem::path> srcFiles;
	std::vector<std::filesystem::path> headers;
	std::vector<std::filesystem::path> resFiles;
	std::vector<std::filesystem::path> sceneFiles;

	for(auto& file : files)
	{
		switch(file_type[file.extension().string()])
		{
			case 1:
				srcFiles.push_back(file);
				break;
			case 2:
				headers.push_back(file);
				break;
			case 3:
				resFiles.push_back(file);
				break;
			case 4:
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
			"<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"
			"<Project DefaultTargets=\"Build\" ToolsVersion=\"17.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\r\n"
			"<ItemGroup Label=\"ProjectConfigurations\">\r\n"
			"	<ProjectConfiguration Include=\"Debug|Win32\">\r\n"
			"		<Configuration>Debug</Configuration>\r\n"
			"		<Platform>Win32</Platform>\r\n"
			"	</ProjectConfiguration>\r\n"
			"		<ProjectConfiguration Include=\"Release | Win32\">\r\n"
			"			<Configuration>Release</Configuration>\r\n"
			"			<Platform>Win32</Platform>\r\n"
			"		</ProjectConfiguration>\r\n"
			"	</ItemGroup>\r\n"
			"	<Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.default.props\" />\r\n"
			"	<PropertyGroup>\r\n"
			"		<ConfigurationType>Application</ConfigurationType>\r\n"
			"		<PlatformToolset>v142</PlatformToolset>\r\n"
			"	</PropertyGroup>\r\n"
			"	<PropertyGroup>\r\n"
			"		<PreferredToolArchitecture>x64</PreferredToolArchitecture>\r\n"
			"	</PropertyGroup>\r\n"
			"  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\" />\r\n"
			"  <ItemGroup>\r\n";

		for(auto& file : srcFiles)
		{
			vcproj += "    <ClCompile Include=\"" + file.string() + "\" />\r\n";
		}

		vcproj +=	"  </ItemGroup>\r\n"
					"  <ItemGroup>\r\n";

		for(auto& file : headers)
		{
			vcproj += "    <ClInclude Include=\"" + file.string() + "\" />\r\n";
		}

		vcproj +=	"  </ItemGroup>\r\n"
					"  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.Targets\" />\r\n"
					"</Project>\r\n";

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
