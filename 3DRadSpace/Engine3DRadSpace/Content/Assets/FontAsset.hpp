#pragma once
#include "../IAsset.hpp"

namespace Engine3DRadSpace
{
	class IService;
	namespace Graphics
	{
		class IGraphicsDevice;
		class Font;
	}

	namespace Internal
	{
		struct AssetUUIDReader;
	}

	namespace Content::Assets
	{
		class E3DRSP_CONTENT_ASSETS_EXPORT FontAsset final : public IAsset
		{
			std::unique_ptr<Graphics::Font> _font;

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
			
			Graphics::Font* GetFont() const noexcept;
			Graphics::Font* operator->() const noexcept;
			operator Graphics::Font& () const;

			~FontAsset() override = default;

			friend struct Internal::AssetUUIDReader;
		};
	}
}
