#include "SourceGenerator.hpp"
#include <Windows.h>

extern std::unordered_map<std::string, int> file_type;

static bool generate_main_cpp(const ProjectInfo& info)
{
	std::filesystem::path main_cpp_path = info.Output / "main.cpp";

	if(std::filesystem::exists(main_cpp_path)) return true;

	std::string main;

	auto escapePathString = [](const std::string& str) -> const std::string
	{
		std::string r;

		for(auto chr : str)
		{
			if(chr == '\\') r.push_back('\\');
			r.push_back(chr);
		}

		return r;
	};

	if(std::filesystem::exists(info.EntryProject))
	{
		main = std::format(
			"#include <Engine3DRadSpace/Games/Game.hpp>\n"
			"\n"
			"class MyGame : public Engine3DRadSpace::Game\n"
			"{{\n"
			"public:\n"
			"	MyGame() : Game(\"{}\") \n"
			"	{{\n"
			"		AppendScene(\"{}\");\n"
			"	}}\n"
			"	~MyGame() override = default;\n"
			"}};\n"
			"\n"
			"int main()\n"
			"{{\n"
			"	MyGame game;\n"
			"	game.Run();\n"
			"}}",
			info.Name,
			escapePathString(info.EntryProject.string())
		);
	}
	else
	{
		main = std::format(
			"#include <Engine3DRadSpace/Games/Game.hpp>\n"
			"\n"
			"	class MyGame : public Engine3DRadSpace::Game\n"
			"{{\n"
			"public:\n"
			"	MyGame() : Game(\"{}\") {{}}\n"
			"	~MyGame() override = default;\n"
			"}};\n"
			"\n"
			"int main()\n"
			"{{\n"
			"	MyGame game;\n"
			"	game.ClearColor = Engine3DRadSpace::Math::Colors::Red;\n"
			"	game.Run();\n"
			"}}",
			info.Name
		);
	}

	std::ofstream mainFile(main_cpp_path);
	if(!mainFile.is_open())
	{
		std::println("[ERROR] Failed to create main.cpp file.");
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

		std::println("[ERROR] Failed to copy file {}", strFilename);
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

		//Generate a blank 3DRadSpace application:
		// {0} = Headers location
		// {1} = Debug binaries location (dll+lib)
		// {2} = Release binaries location
		// {3} = lib filenames

		auto pathHeaders = std::filesystem::canonical(".\\\\Include\\").string();
		auto pathDebugBin = std::filesystem::canonical(".\\\\Bin\\Windows-x64\\Debug\\").string();
		auto pathReleaseBin = std::filesystem::canonical(".\\\\Bin\\Windows-x64\\Release\\").string();

		std::string libraries =
			"3DRadSpace.Core.lib;"
			"3DRadSpace.Math.lib;"
			"3DRadSpace.Audio.lib;"
			"3DRadSpace.Content.lib;"
			"3DRadSpace.Content.Assets.lib;"
			"3DRadSpace.Games.lib;"
			"3DRadSpace.Graphics.lib;"
			"3DRadSpace.Graphics.DirectX11.lib;"
			"3DRadSpace.Graphics.Null.lib;"
			"3DRadSpace.Graphics.Primitives.lib;"
			"3DRadSpace.Graphics.Rendering.lib;"
			"3DRadSpace.Input.lib;"
			"3DRadSpace.Logging.lib;"
			"3DRadSpace.Native.lib;"
			"3DRadSpace.Objects.lib;"
			"3DRadSpace.Objects.Impl.lib;"
			"3DRadSpace.Physics.lib;"
			"3DRadSpace.Physics.NVPhysX.lib;"
			"3DRadSpace.Physics.Objects.lib;"
			"3DRadSpace.Projects.lib;"
			"3DRadSpace.Reflection.lib;"
			"3DRadSpace.Scripting.lib;";

		std::string vcproj = std::format((
			"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
			"<Project DefaultTargets=\"Build\" ToolsVersion=\"17.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\n"
			"<ItemGroup Label=\"ProjectConfigurations\">\n"
			"	<ProjectConfiguration Include=\"Debug|x64\">\n"
			"		<Configuration>Debug</Configuration>\n"
			"		<Platform>x64</Platform>\n"
			"	</ProjectConfiguration>\n"
			"	<ProjectConfiguration Include=\"Release|x64\">\n"
			"		<Configuration>Release</Configuration>\n"
			"		<Platform>x64</Platform>\n"
			"	</ProjectConfiguration>\n"
			"</ItemGroup>\n"
			"	<PropertyGroup Label = \"Globals\" >\n"
			"		<ProjectGuid>{{F9609F33-AFCC-FE4D-8919-BC1CD1A400E1}}</ProjectGuid>\n"
			"		<WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>\n"
			"	</PropertyGroup>\n"
			"	<Import Project = \"$(VCTargetsPath)\\Microsoft.Cpp.default.props\"/>\n"
			"	<PropertyGroup>\n"
			"		<ConfigurationType>Application</ConfigurationType>\n"
			"		<PlatformToolset>v145</PlatformToolset>\n"
			"	</PropertyGroup>\n"
			"	<PropertyGroup>\n"
			"		<PreferredToolArchitecture>x64</PreferredToolArchitecture>\n"
			"	</PropertyGroup>\n"
			"	<ItemDefinitionGroup Condition = \"'$(Configuration)|$(Platform)'=='Debug|x64'\">\n"
			"		<ClCompile>\n"
			"			<AdditionalIncludeDirectories>{0}; %(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>\n"
			"			<LanguageStandard>stdcpplatest</LanguageStandard>\n"
			"		</ClCompile>\n"
			"		<Link>\n"
			"			<AdditionalLibraryDirectories>{1}; %(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>\n"
			"			<AdditionalDependencies>{3} %(AdditionalDependencies) </AdditionalDependencies>\n"
			"		</Link>\n"
			"		<PostBuildEvent>\n"
			"			<Command>xcopy /y /d \"{1}\\*.dll\" \"$(TargetDir)\"</Command>\n"
			"		</PostBuildEvent>\n"
			"	</ItemDefinitionGroup>\n"
			"	<ItemDefinitionGroup Condition = \"'$(Configuration)|$(Platform)'=='Release|x64'\">\n"
			"		<ClCompile>\n"
			"			<AdditionalIncludeDirectories>{0}\\; %(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>\n"
			"			<LanguageStandard>stdcpplatest</LanguageStandard>\n"
			"		</ClCompile>\n"
			"		<Link>\n"
			"			<AdditionalDependencies>{3} %(AdditionalDependencies)</AdditionalDependencies>\n"
			"			<AdditionalLibraryDirectories>{2}; %(AdditionalLibraryDirectories) </AdditionalLibraryDirectories>\n"
			"		</Link>\n"
			"		<PostBuildEvent>\n"
			"			<Command>xcopy /y /d \"{2}\\*.dll\" \"$(TargetDir)\"</Command>\n"
			"		</PostBuildEvent>\n"
			"	</ItemDefinitionGroup>\n"
			"	<Import Project = \"$(VCTargetsPath)\\Microsoft.Cpp.props\"/>\n"
			"	<ItemGroup>\n"),
			pathHeaders,
			pathDebugBin,
			pathReleaseBin,
			libraries
		);

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
			std::println("[ERROR] Failed to create MSVC project file.");
			return false;
		}
		vcprojFile << vcproj;

		return true;
	}

	return false;
}
