#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Plugins
{
	/// <summary>
	/// Plugin information.
	/// </summary>
	struct PluginInfo
	{
		const char* Name;
		const char* Version;

		const char* Author;
		const char* Description;
		const char* Homepage;

		const char* IconFilename;
	};
}