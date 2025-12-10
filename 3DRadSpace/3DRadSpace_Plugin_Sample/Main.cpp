#include <Engine3DRadSpace/Logging/Message.hpp>
#include <Engine3DRadSpace/Plugins/EditorPlugin.hpp>

using namespace Engine3DRadSpace::Plugins;
using namespace Engine3DRadSpace::Logging;

extern "C"
{
	__declspec(dllexport) bool PluginMain();
	__declspec(dllexport) bool PluginUnload();
	__declspec(dllexport) PluginInfo LoadPluginInfo();
}

bool PluginMain()
{
	SetLastMessage("Hello world!");
	return true;
}

bool PluginUnload()
{
	SetLastMessage("Unloading example plugin");
	return true;
}

PluginInfo LoadPluginInfo()
{
	return PluginInfo
	{
		.Name = "3DRadSpace Hello World Plugin",
		.Version = "1.0.0",
		.Author = "3DRadSpace",

		.Description = "Hello world",
		.Homepage = "3dradspace.github.io",
		.IconFilename = "3DRadSpace.png"
	};
}