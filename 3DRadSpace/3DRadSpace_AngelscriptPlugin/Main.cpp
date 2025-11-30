#include <Engine3DRadSpace\Plugins\EditorPlugin.hpp>
#include <Engine3DRadSpace\Plugins\CustomObject.hpp>
#include "AngelScriptObject.hpp"
#include "AngelscriptWrapper.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Angelscript;
using namespace Engine3DRadSpace::Plugins;
using namespace Engine3DRadSpace::Reflection;

std::unique_ptr<AngelScriptWrapper> _angelscriptWrapper;

REFL_FWD(AngelScriptObject);

std::array<Engine3DRadSpace::Reflection::ReflectedObject*, 1> newObjects =
{
	&AngelScriptObjectReflInstance
};

extern "C"
{
	__declspec(dllexport) bool PluginMain()
	{
		_angelscriptWrapper = std::make_unique<AngelScriptWrapper>();
		return true;
	}

	__declspec(dllexport) bool PluginUnload()
	{
		_angelscriptWrapper.reset();
		return true;
	}

	__declspec(dllexport) PluginInfo LoadPluginInfo()
	{
		return PluginInfo
		{
			.Name = "3DRadSpace Angelscript plugin",
			.Version = "0.1.0-Alpha",
			.Author = "3DRadSpace",

			.Description = "AngelScript scripting language support for 3DRadSpace.",
			.Homepage = "3dradspace.github.io",
			.IconFilename = "AngelScript.png"
		};
	}

	__declspec(dllexport) std::span<ReflectedObject*> LoadCustomObjects()
	{
		return newObjects;
	}
}