#pragma once
#include "IAssetWrapper.hpp"
#include "../../Graphics/Font.hpp"

namespace Engine3DRadSpace
{
	namespace Internal
	{
		struct AssetUUIDReader;
	}

	namespace Content::Assets
	{
		class E3DRSP_CONTENT_ASSETS_EXPORT FontAsset final : public IAssetWrapper<Graphics::Font>
		{
			FontAsset(Internal::AssetUUIDReader dummy);
		public:
			FontAsset(IService* device, const std::filesystem::path &path);

			/// <summary>
			/// UUID of the Font type. Used internally.
			/// </summary>
			/// <returns>UUID</returns>
			Reflection::UUID GetUUID() const noexcept override;
			/// <summary>
			/// Supported file types, used internally.
			/// </summary>
			/// <returns></returns>
			const char* FileExtension() const noexcept override;

			std::type_index InitializationService() const noexcept override;

			~FontAsset() override = default;

			friend struct Internal::AssetUUIDReader;
		};
	}
}
