#include "LibraryLoader.hpp"

void* Engine3DRadSpace::OS::Load_Library(const std::filesystem::path& path)
{
	auto str = path.string();
#ifdef _WIN32
	return static_cast<void*>(LoadLibraryA(str.c_str()));
#elif _LINUX
	return dlopen(str.c_str(), RTLD_NOW);
#endif
}
