#include <Engine3DRadSpace\Plugins\EditorPlugin.hpp>
#include <Engine3DRadSpace\Plugins\CustomObject.hpp>
#include "AngelScriptObject.hpp"
#include "AngelscriptWrapper.hpp"
#include <Engine3DRadSpace/Core/RawSpan.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Angelscript;
using namespace Engine3DRadSpace::Plugins;
using namespace Engine3DRadSpace::Reflection;

std::unique_ptr<AngelScriptWrapper> p_angelscriptWrapper;

REFL_FWD(AngelScriptObject);

E3DRSP_RawSpan newObjects =
{
	.Ptr = &AngelScriptObjectReflInstance,
	.Size = 1u
};

extern "C" //Prevent name mangling.
{
	__declspec(dllexport) bool PluginMain()
	{
		p_angelscriptWrapper = std::make_unique<AngelScriptWrapper>();
		return true;
	}

	__declspec(dllexport) bool PluginUnload()
	{
		p_angelscriptWrapper.reset();
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

	__declspec(dllexport) E3DRSP_RawSpan LoadCustomObjects()
	{
		return newObjects;
	}
}