#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Plugins
{
	/// <summary>
	/// Plugin information.
	/// </summary>
	struct PluginInfo
	{
		std::string Name;
		std::string Version;

		std::string Author;
		std::string Description;
		std::string Homepage;

		std::string IconFilename;
	};
}