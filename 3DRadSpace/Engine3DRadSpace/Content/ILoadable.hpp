#pragma once
#include "ContentManager.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT ILoadable
	{
	public:
		/// <summary>
		/// Loads object's assets.
		/// </summary>
		/// <param name="content"></param>
		virtual void Load() = 0;
		/// <summary>
		/// Reloads assets from an other path.
		/// </summary>
		/// <param name="content">Content manager used to load the asset(s).</param>
		/// <param name="path">Specified asset path</param>
		virtual void Load(const std::filesystem::path& path) = 0;
		virtual ~ILoadable() = default;
	};
}