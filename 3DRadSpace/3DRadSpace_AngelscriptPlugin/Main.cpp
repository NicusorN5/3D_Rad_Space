#include <Engine3DRadSpace\Plugins\EditorPlugin.hpp>
#include <Engine3DRadSpace\Plugins\CustomObject.hpp>
#include "AngelScriptObject.hpp"
#include "AngelscriptWrapper.hpp"

std::unique_ptr<Engine3DRadSpace_Angelscript::AngelScriptWrapper> _angelscriptWrapper;

extern "C"
{
	__declspec(dllexport) bool PluginMain()
	{
		_angelscriptWrapper = std::make_unique<Engine3DRadSpace_Angelscript::AngelScriptWrapper>();
		return true;
	}

	__declspec(dllexport) bool PluginUnload()
	{
		_angelscriptWrapper.reset();
		return true;
	}

	__declspec(dllexport) Engine3DRadSpace::Plugins::PluginInfo LoadPluginInfo()
	{
		return Engine3DRadSpace::Plugins::PluginInfo
		{
			.Name = "3DRadSpace Angelscript plugin",
			.Version = "0.1.0-Alpha",
			.Author = "3DRadSpace",

			.Description = "AngelScript scripting language support for 3DRadSpace.",
			.Homepage = "3dradspace.github.io",
			.IconFilename = "AngelScript.png"
		};
	}
}