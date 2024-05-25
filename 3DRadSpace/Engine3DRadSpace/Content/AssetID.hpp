#pragma once
#include "IAsset.hpp"

namespace Engine3DRadSpace::Content
{
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