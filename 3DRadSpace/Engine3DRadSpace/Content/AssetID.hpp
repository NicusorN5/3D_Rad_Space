#pragma once
#include "IAsset.hpp"

namespace Engine3DRadSpace::Content
{
	/// <summary>
	/// Numerical identified of an asset, paired with a template type.
	/// </summary>
	/// <typeparam name="T">T must be a AssetType - must inherit IAsset and be constructible from a factory class and a path.</typeparam>
	template<AssetType T>
	struct AssetID
	{
		AssetID() : ID(0) {};
		AssetID(unsigned id) : ID(id) {};
		unsigned ID;

		operator unsigned() const noexcept
		{
			return ID;
		}
	};
}