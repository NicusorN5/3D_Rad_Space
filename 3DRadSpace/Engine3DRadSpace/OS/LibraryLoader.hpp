#pragma once
#include "../Libs.hpp"

/// <summary>
/// OS-related functions to handle libraries, symbols, etc...
/// </summary>

namespace Engine3DRadSpace::OS
{
	/// <summary>
	/// OS-indepedent function that gets a function from a DLL using the function name.
	/// </summary>
	/// <typeparam name="F">Function typedef.</typeparam>
	/// <param name="libraryHandle">Handle of the loaded library.</param>
	/// <param name="name">Function name</param>
	/// <returns></returns>
	template<typename F>
	F GetFunctionFromLibrary(void* libraryHandle, const std::string& name)
	{
#ifdef _WIN32
		auto f = reinterpret_cast<F>(GetProcAddress(static_cast<HMODULE>(libraryHandle), name.c_str()));
#elif _LINUX
		auto f = reinterpret_cast<F>(dlsym(libraryHandle, name));
#endif
		return f;
	}

	/// <summary>
	/// Loads a DLL/library and returns it's handle.
	/// </summary>
	/// <param name="path">Path to DLL/library.</param>
	/// <returns>Module handle of the loaded library.</returns>
	DLLEXPORT void* Load_Library(const std::filesystem::path& path);
}