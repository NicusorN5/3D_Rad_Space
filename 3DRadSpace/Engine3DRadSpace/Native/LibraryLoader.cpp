#include "LibraryLoader.hpp"

void* Engine3DRadSpace::Native::Load_Library(const std::filesystem::path& path)
{
	auto str = path.string();
#ifdef _WIN32
	return static_cast<void*>(LoadLibraryA(str.c_str()));
#elif _LINUX
	return dlopen(str.c_str(), RTLD_NOW);
#endif
}

void Engine3DRadSpace::Native::Free_Library(void* pModule)
{
#ifdef _WIN32
	FreeLibrary(static_cast<HMODULE>(pModule));
#elif _LINUX
	dlclose(pModule);
#endif
}