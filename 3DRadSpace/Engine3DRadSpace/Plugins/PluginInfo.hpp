#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Plugins
{
	/// <summary>
	/// Plugin information.
	/// </summary>
	struct PluginInfo
	{
		const std::string_view& Name;
		const std::string_view& Version;

		const std::string_view& Author;
		const std::string_view& Description;
		const std::string_view& Homepage;

		const std::string_view& IconFilename;
	};
}