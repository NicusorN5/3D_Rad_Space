#pragma once
#include "../IAsset.hpp"

namespace Engine3DRadSpace::Content::Assets
{
	class NullAsset final: public IAsset
	{
	public:
		NullAsset() = default;

		Reflection::UUID GetUUID() const noexcept override;
		const char* FileExtension() const noexcept override;
	};
}