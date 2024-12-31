#include <iostream>
#include <print>
#include <fstream>
#include <unordered_map>
#include <ranges>
#include <vector>
#include <string>

auto main(int argc, char** argv) -> int
{
	std::unordered_map<std::string, int> dict =
	{
		{"-h", 1},
		{"--help", 1},
		{"-v", 2},
		{"--version", 2},
		{"-o", 3},
		{"-output", 3},
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

	std::vector<std::string> files;

	for(int i = 0; i < argc; i++)
	{
		switch(dict[argv[i]])
		{
			case 1:
				std::println("3DRadSpace Compiler v0.1.0a");
				std::println("Tool that invokes a C++ compiler (Windows MSVC) and generates a game from project and source files.");
				std::println("Arguments");
				std::println("Help : -h or --help");
				std::println("Version : -v or --version");
				std::println("Output: -o <output folder> or --output <output folder>");
				return 0;
			case 2:
				std::println("3DRadSpace Compiler v0.1.0a");
				return 0;
		}
	}

	return 0;
}