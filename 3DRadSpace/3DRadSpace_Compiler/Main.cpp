#include "SourceGenerator.hpp"
#include "ProjectBuilder.hpp"

std::unordered_map<std::string, int> dict =
{
	{"-h", 1},
	{"--help", 1},
	{"-v", 2},
	{"--version", 2},
	{"-o", 3},
	{"-output", 3},
	{"--checkcompiler", 4},
	{"--compiler", 4},
	{"-c", 4},
};

std::unordered_map<std::string, int> file_type =
{
	//C++ Source files.
	{".cpp", 1},
	{".hpp", 1},
	{".h", 1},
	//C# source files.
	{".cs", 2},
	//Icon
	{".ico", 3},
	//3DRadSpace scene project
	{".3drsp",4}
};

auto main(int argc, char** argv) -> int
{
	std::println("3DRadSpace Compiler v0.1.0a");

	std::vector<std::filesystem::path> files;
	std::filesystem::path outputFolder;
	std::unique_ptr<std::ofstream> out_f;

	for(int i = 1; i < argc; i++)
	{
		switch(dict[argv[i]])
		{
			case 1:
				std::println("Tool that invokes a C++ compiler (Windows MSVC) and generates a game from project and source files.");
				std::println("Arguments");
				std::println("Help : -h or --help");
				std::println("Version : -v or --version");
				std::println("Output: -o <output folder> or --output <output folder>");
				return 0;
			case 2:
				std::println("Version: v0.1.0-Alpha");
				return 0;
			case 3:
				if(i + 1 < argc)
					outputFolder = std::filesystem::path(argv[i + 1]);
				else
					std::println("[ERROR]-output must specify output");
				break;
			case 4:
				{
					std::ifstream cache("compiler_cache.json");
					if(cache.good())
					{

					}
					auto compiler = FindCompiler();
					if(!compiler.has_value())
					{
						std::println("[!]No compatible compiler not found.");
						return 0;
					}
					else
					{
						switch(compiler->CompilerType)
						{
							case Compiler::Type::MSVC:
								std::println("Found MSVC compiler: {}", compiler->Path);
								break;
							case Compiler::Type::Clang:
								std::println("Found Clang compiler: {}", compiler->Path);
								break;
							case Compiler::Type::GCC:
								std::println("Found GCC compiler: {}", compiler->Path);
								break;
							default:
								std::println("[!]Unknown compiler type.");
								return 0;
						}
					}
					return 0;
				}
			default:
				if(!std::filesystem::exists(argv[i]))
				{
					std::println("[WARNING] Specified file {} doesn't exist!", argv[i]);
				}
				else files.emplace_back(argv[i]);
				break;
		}
	}

	bool hasIcon = false;

	if(files.empty())
	{
		std::println("No files provided. Exiting");
		return 0;
	}

	if(!out_f)
	{
		std::println("[INFO]Output folder not specified. Using current directory.");
		outputFolder = std::filesystem::current_path().append("/BuildProject");

		if(std::filesystem::exists(outputFolder))
		{
			//Erase folder with all of its contents.
			std::filesystem::remove_all(outputFolder);
		}
		//Recreate folder
		std::filesystem::create_directory(outputFolder);
	}

	std::println("3DRadSpace Compiler v0.1.0a");
	std::println("[1/5] Checking project files:");
	for(auto& file : files)
	{
		std::string type;
		switch(file_type[file.extension().string()])
		{
			case 1:
				type = "C++ source file";
				break;
			case 2:
				type = "C# source file";
				break;
			case 3:
				type = "Icon resource";
				hasIcon = true;
				break;
			case 4:
				type = "3DRadSpace Scene";
				break;
			default:
				type = "Unknown type";
				break;

		}
		std::println("- {}: {}", type, file.string());
	}

	std::println("[2/5] Checking envoirement...");

	int r = 0;
	std::optional<Compiler> compiler = std::nullopt;

	std::ifstream cache("compiler_cache.json");
	if(cache.good())
	{
		std::println("Found cached envoirement settings...");

		nlohmann::json j;
		cache >> j;
		
		std::filesystem::path devenv = j["devenv"].get<std::string>();
		if(!devenv.empty())
		{
			if(std::filesystem::exists(devenv))
			{
				std::println("Found Visual Studio devenv: {}", devenv.string());
				cache.close();

				compiler = Compiler
				{
					.CompilerType = Compiler::Type::MSVC,
					.Path = devenv.string()
				};
				goto generate;
			}
			else
			{
				std::println("[WARNING]Cached devenv path doesn't exist.");
				cache.close();
				std::filesystem::remove("compiler_cache.json");
				goto find_compiler;
			}
		}

		std::filesystem::path clang = j["clang"].get<std::string>();
		if(!clang.empty())
		{
			if(std::filesystem::exists(clang))
			{
				std::println("Found Clang: {}", clang.string());
				cache.close();
				compiler = Compiler
				{
					.CompilerType = Compiler::Type::Clang,
					.Path = clang.string()
				};
				goto generate;
			}
			else
			{
				std::println("[WARNING]Cached clang path doesn't exist.");
				cache.close();
				std::filesystem::remove("compiler_cache.json");
				goto find_compiler;
			}
		}

		std::filesystem::path gcc = j["gcc"].get<std::string>();
		if(!gcc.empty())
		{
			if(std::filesystem::exists(gcc))
			{
				std::println("Found GCC: {}", gcc.string());
				cache.close();
				compiler = Compiler
				{
					.CompilerType = Compiler::Type::GCC,
					.Path = gcc.string()
				};
				goto generate;
			}
			else
			{
				std::println("[WARNING]Cached gcc path doesn't exist.");
				cache.close();
				std::filesystem::remove("compiler_cache.json");
				goto find_compiler;
			}
		}

		std::println("[WARNING]Cached compiler settings are invalid.");
		std::filesystem::remove("compiler_cache.json");
	}

find_compiler:
	compiler = FindCompiler();
	if(!compiler.has_value())
	{
		return -1;
	}

	SaveCompilerCache(compiler.value());
generate:
	std::println("[3/5] Generating project files...");
	GenerateProject(outputFolder, files, compiler->CompilerType);
build:
	std::println("[4/5] Building project...");

	switch(compiler->CompilerType)
	{
		case Compiler::Type::MSVC:
			MSVC_Build(outputFolder, compiler->Path);
			break;
		case Compiler::Type::GCC:
			GCC_Build(outputFolder, compiler->Path);
			break;
		case Compiler::Type::Clang:
			Clang_Build(outputFolder, compiler->Path);
			break;
		default:
			std::println("[FATAL] Unknown compiler type.");
			return -1;
	}
	return 0;
}