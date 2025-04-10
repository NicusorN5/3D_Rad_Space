#include "EditorPlugin.hpp"
#include "../OS/LibraryLoader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Plugins;
using namespace Engine3DRadSpace::OS;

std::expected<PluginInfo, PluginLoadingError> Engine3DRadSpace::Plugins::LoadPlugin(const std::filesystem::path& pluginPath)
{
	auto plugin = Load_Library(pluginPath);
	if(!plugin) return std::unexpected(PluginLoadingError::UnableToLoadPluginLibrary);

	auto initialize_fn = GetFunctionFromLibrary<PluginMain>(plugin, "PluginMain");
	if(!initialize_fn) return std::unexpected(PluginLoadingError::NotA3DRadSpacePlugin);

	auto get_info = GetFunctionFromLibrary<LoadPluginInfo>(plugin, "LoadPluginInfo");
	if(!get_info) return std::unexpected(PluginLoadingError::NotA3DRadSpacePlugin);

	if(!initialize_fn()) return std::unexpected(PluginLoadingError::InitializationFunctionFailure);

	return get_info();
}
