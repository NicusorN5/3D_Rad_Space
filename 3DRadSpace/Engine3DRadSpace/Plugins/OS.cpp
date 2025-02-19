#include "OS.hpp"

void* Engine3DRadSpace::Plugins::Load_Library(const std::filesystem::path& path)
{
	auto str = path.string();
#ifdef _WIN32
	return static_cast<void*>(LoadLibraryA(str.c_str()));
#elif
	return dlopen(str.c_str(), RTLD_NOW);
#endif
}
