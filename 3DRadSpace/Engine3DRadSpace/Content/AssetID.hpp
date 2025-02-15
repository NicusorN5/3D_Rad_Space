/// ------------------------------------------------------------------------------------------------
/// File:   Content/AssetID.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
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