#include "CSharpScript.hpp"
#include "NETCoreHost.hpp"
#include "../../Core/RawSpan.h"
#include "../../Logging/Message.hpp"
#include "../../Logging/Warning.hpp"
#include "../../Plugins/EditorPlugin.hpp"
#include "../../Native/LibraryLoader.hpp"

//https://github.com/dotnet/samples/blob/main/core/hosting/src/NativeHost/nativehost.cpp

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Native;
using namespace Engine3DRadSpace::Plugins;

extern "C"
{
	__declspec(dllexport) bool PluginMain();
	__declspec(dllexport) bool PluginUnload();
	__declspec(dllexport) PluginInfo LoadPluginInfo();
	__declspec(dllexport) E3DRSP_RawSpan LoadCustomObjects();
}

string_t fxrPath;
extern load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer;

bool PluginMain()
{
	if (!load_hostfxr())
	{
		Logging::SetLastWarning("load_hostfxr() failed!");
		return false;
	}

	load_assembly_and_get_function_pointer = get_dotnet_load_assembly(fxrPath.c_str());

	if (load_assembly_and_get_function_pointer == nullptr)
	{
		Logging::SetLastWarning("get_dotnet_load_assembly() is null!");
		return false;
	}

	wchar_t modulePath[MAX_PATH]{};
	GetModuleFileNameW(nullptr, modulePath, MAX_PATH);

	wchar_t host_path[MAX_PATH]{};
#if _WINDOWS
	auto size = GetFullPathNameW(modulePath, sizeof(modulePath) / sizeof(char_t), host_path, nullptr);
	assert(size != 0);
#else
	auto resolved = realpath(argv[0], host_path);
	assert(resolved != nullptr);
#endif

	string_t root_path = host_path;
	auto pos = root_path.find_last_of('\\');
	assert(pos != string_t::npos);
	root_path = root_path.substr(0, pos + 1);

	return true;
}

bool PluginUnload()
{
	return true;
}

PluginInfo LoadPluginInfo()
{
	return PluginInfo
	{
		.Name = "3DRadSpace C# Scripting",
		.Version = "0.1.0 Alpha",
		.Author = "3DRadSpace",

		.Description = "Hello world",
		.Homepage = "3dradspace.github.io",
		.IconFilename = "3DRadSpace.png"
	};
}

E3DRSP_RawSpan LoadCustomObjects(void)
{
	E3DRSP_RawSpan newObjects =
	{
		.Ptr = &CSharpScriptReflInstance,
		.Size = 1u
	};

	return newObjects;
}