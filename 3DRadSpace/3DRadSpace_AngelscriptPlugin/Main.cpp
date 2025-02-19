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
	}

	__declspec(dllexport) Engine3DRadSpace::Plugins::PluginInfo  
}