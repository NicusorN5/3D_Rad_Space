#pragma once
#include "../IAsset.hpp"

namespace Engine3DRadSpace::Internal
{
	struct AssetUUIDReader;
}

namespace Engine3DRadSpace::Content::Assets
{
	class E3DRSP_CONTENT_ASSETS_EXPORT NullAsset final: public IAsset
	{
		NullAsset(Internal::AssetUUIDReader dummy);
	public:
		NullAsset() = default;
		NullAsset(const std::filesystem::path& dummy);

		NullAsset(NullAsset&&) noexcept= default;
		NullAsset& operator=(NullAsset&&) noexcept = default;

		Reflection::UUID GetUUID() const noexcept override;
		const char* FileExtension() const noexcept override;

		friend class Internal::AssetUUIDReader;
	};
}