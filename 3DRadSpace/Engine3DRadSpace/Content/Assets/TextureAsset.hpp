#pragma once
#include "../IAsset.hpp"

namespace Engine3DRadSpace
{
	class IService;
	namespace Graphics
	{
		class ITexture2D;
	}
	namespace Internal
	{
		struct AssetUUIDReader;
	}

	namespace Content::Assets
	{
		class E3DRSP_CONTENT_ASSETS_EXPORT TextureAsset final : public IAsset
		{
			std::unique_ptr<Graphics::ITexture2D> _texture;

			TextureAsset(Internal::AssetUUIDReader dummy);
		public:
			TextureAsset(IService* device, const std::filesystem::path& path);

			TextureAsset(const TextureAsset&) = delete;
			TextureAsset(TextureAsset&&) noexcept = default;

			TextureAsset& operator=(const TextureAsset&) = delete;
			TextureAsset& operator=(TextureAsset&&) noexcept = default;

			Reflection::UUID GetUUID() const noexcept override;
			const char* FileExtension() const noexcept override;
			std::type_index InitializationService() const noexcept override;

			Graphics::ITexture2D* GetTexture() const noexcept;

			~TextureAsset() override = default;

			friend class Internal::AssetUUIDReader;
		};
	}
}