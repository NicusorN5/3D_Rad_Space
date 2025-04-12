#include "CompilerDetector.hpp"

#ifdef _WIN32

#include <Windows.h>
#include <tlhelp32.h>

/// <summary>
/// Finds devenv by creating a empty project.
/// </summary>
/// <returns></returns>
static auto find_vs2() -> std::optional<std::filesystem::path>
{
	std::ofstream dummy("dummy.vcxproj");
	if(!dummy.good())
	{
		std::println("[ERROR] Failed to create dummy project");
		return std::nullopt;
	}
	INT_PTR r = reinterpret_cast<INT_PTR>(ShellExecuteA(
		nullptr,
		"open", 
		"dummy.vcxproj",
		nullptr,
		nullptr, 
		SW_FORCEMINIMIZE
	));
	if(r != 0)
	{
		std::println("[ERROR] Failed to open devenv.");
		return std::nullopt;
	}

	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(snapshot == INVALID_HANDLE_VALUE)
	{
		std::println("[ERROR] Failed to create snapshot");
		return std::nullopt;
	}

	HANDLE procVS = nullptr;
	
	if(Process32First(snapshot, &entry))
	{
		while(Process32Next(snapshot, &entry));
		{
			if(std::wstring(entry.szExeFile) == L"devenv.exe")
			{
				procVS = OpenProcess(
					PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_TERMINATE,
					FALSE,
					entry.th32ProcessID
				);

				if(procVS == nullptr)
				{
					goto fail;
				}

				wchar_t vsPath[MAX_PATH];
				DWORD lenPath = MAX_PATH;
				
				BOOL r = QueryFullProcessImageNameW(procVS, 0, vsPath, &lenPath);
				if(!r)
				{
					std::println("[ERROR] Failed to query full process image name");
					goto fail;
				}

				CloseHandle(snapshot);
				TerminateProcess(procVS, 0); //Terminate VS as it was only needed for getting the path.
				CloseHandle(procVS);
				return std::filesystem::path(vsPath);
			}
		} 
	}

fail:
	if(snapshot) CloseHandle(snapshot);
	if(procVS) CloseHandle(procVS);
	return std::nullopt;
}
#endif

std::optional<Compiler> FindCompiler()
{
#ifdef _WIN32
	//Find Visual Studio

	std::println("Finding MSVC: Attempt 1 - vswhere");
	//CMD.exe requires two " 
	int r = std::system("\"\"%ProgramFiles(x86)%\\Microsoft Visual Studio\\Installer\\vswhere.exe\" -nologo -latest -property productPath > temp.txt\"");
	if(r == 0)
	{
		std::ifstream where("temp.txt");

		std::string path;
		std::getline(where, path);

		where.close();
		std::filesystem::remove("temp.txt");

		std::println("[SUCCESS] Found MSVC");
		return Compiler
		{
			.CompilerType = Compiler::Type::MSVC,
			.Path = path
		};
	}

	std::println("Finding MSVC: Attempt 2 - devenv");
	auto devenv = find_vs2();
	if(devenv.has_value())
	{
		std::println("[SUCCESS] Found MSVC");
		return Compiler
		{
			.CompilerType = Compiler::Type::MSVC,
			.Path = devenv.value().string()
		};
	}
	else
	{
		std::println("[FAIL] Failed to find MSVC.");
	}

#endif // _WIN32
	//Find clang (could work with both Windows and Linux).
	r = system("clang --version");
	if(r == 0)
	{
		std::println("[SUCCESS] Found clang");
		return Compiler
		{
			.CompilerType = Compiler::Type::Clang,
			.Path = "clang"
		};
	}

#ifdef _LINUX
	else
	{
		//Otherwise find GCC.
		r = system("gcc");
		if(r == 0)
		{
			std::print("[SUCCESS] Found gcc");
			return Compiler
			{
				.Type = Compiler::Type::GCC,
				.Path = "gcc"
			};
		}
	}
#endif
	std::println("[ERROR] No compatible C++ compiler found...");
	return std::nullopt;
}

void SaveCompilerCache(const Compiler& compiler)
{
	std::ofstream cache("compiler_cache.json");
	if(!cache.good())
	{
		std::println("[ERROR] Failed to open cache file.");
		return;
	}

	nlohmann::json j;
	switch(compiler.CompilerType)
	{
		case Compiler::Type::MSVC:
			j["devenv"] = compiler.Path;
			break;
		case Compiler::Type::Clang:
			j["clang"] = compiler.Path;
			break;
		case Compiler::Type::GCC:
			j["gcc"] = compiler.Path;
			break;
		default:
			std::println("[ERROR] Unknown compiler type when saving compiler cache.");
			return;
	}
}

void Compiler::Print()
{
	switch(CompilerType)
	{
		case Compiler::Type::MSVC:
			std::println("Found MSVC compiler: {}", Path);
			break;
		case Compiler::Type::Clang:
			std::println("Found Clang compiler: {}", Path);
			break;
		case Compiler::Type::GCC:
			std::println("Found GCC compiler: {}", Path);
			break;
		default:
			std::println("[!]Unknown compiler type.");
	}
}