#pragma once
#include "PluginInfo.hpp"

namespace Engine3DRadSpace::Plugins
{
	/// <summary>
	/// Returns plugin base information.
	/// </summary>
	/// <returns>
	/// Plugin information.
	/// </returns>
	typedef PluginInfo (*LoadPluginInfo)();

	/// <summary>
	/// Entry base function for a 3DRadSpace plugin.
	/// </summary>
	/// <returns>
	/// True if succeded.
	/// </returns>
	/// <remarks>
	/// When called, PluginMain has to:
	/// - Load resources related to the plugin itself, such as images, windows..., etc. Meaning that it is safe to create windows, display messages boxes here, unline Windows's in DllMain.
	/// - Define new asset types, if any
	// - Initialize reflection data for custom objects, if any
	/// - Optionally find the editor window, and apply modifications and hooks.
	/// If failed, return false, then call Logging::SetLastError() to report the failure.
	/// </remarks>
	typedef bool (*PluginMain)();

	/// <summary>
	/// Called when unloading the plugin.
	/// </summary>
	/// <returns>
	/// True if succeded.
	/// </returns>
	typedef bool (*PluginUnload)();

	/// <summary>
	/// Error when attempted to load a 3DRadSpace plugin.
	/// </summary>
	enum class PluginLoadingError
	{
		/// <summary>
		/// Returned if the library module coudln't be loaded.
		/// </summary>
		UnableToLoadPluginLibrary,
		/// <summary>
		/// Returned if the loaded library/DLL doesn't have the LoadPluginInfo() or PluginMain() functions.
		/// </summary>
		NotA3DRadSpacePlugin,
		/// <summary>
		/// PluginMain() was called, but it returned false.
		/// </summary>
		InitializationFunctionFailure,
	};

	/// <summary>
	/// Loads a plugin for the editor.
	/// </summary>
	/// <returns>
	/// Plugin information if succeded, or a PluginLoadingError enum value.
	/// </returns>
	/// <param name="pluginPath"></param>
	std::expected<PluginInfo, PluginLoadingError> E3DRSP_PLUGINS_EXPORT LoadPlugin(const std::filesystem::path& pluginPath);
}