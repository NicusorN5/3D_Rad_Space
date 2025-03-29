#pragma once
#include "../IAsset.hpp"

namespace Engine3DRadSpace::Internal
{
	struct AssetUUIDReader;
}

namespace Engine3DRadSpace::Content::Assets
{
	class NullAsset final: public IAsset
	{
		NullAsset(Internal::AssetUUIDReader dummy);
	public:
		NullAsset() = default;
		NullAsset(const std::filesystem::path& dummy);

		Reflection::UUID GetUUID() const noexcept override;
		const char* FileExtension() const noexcept override;

		friend class Internal::AssetUUIDReader;
	};
}