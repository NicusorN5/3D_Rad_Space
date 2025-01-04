#pragma once
#include "Glyph.hpp"
#include "../Content/IAsset.hpp"
#include "../GraphicsDevice.hpp"
#include "..\Internal\AssetUUIDReader.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT Font : public Content::IAsset
	{
		class FontManager
		{
		public:
			FontManager();

			FontManager(const FontManager&) = delete;
			FontManager(FontManager&&) = delete;
			FontManager& operator=(const FontManager&) = delete;
			FontManager& operator=(FontManager&&) = delete;

			~FontManager();
		};

		bool _valid;
		
		void* _font;
		std::string _supportedCharacters;

		GraphicsDevice* _device;

		static FontManager _manager;
	
		std::vector<std::pair<Glyph, Math::Rectangle>> _glyphs;
		std::unique_ptr<Texture2D> _texture;
		unsigned _size;

		Font(Internal::AssetUUIDReader dummy);
	public:
		Font(GraphicsDevice* device, const std::filesystem::path &path, unsigned size, const char* supportedCharacters = nullptr);
		Font(GraphicsDevice* device, const std::filesystem::path &path);

		Font(const Font&) = delete;
		Font(Font&& font) noexcept = default;

		Font& operator=(const Font&) = delete;
		Font& operator=(Font&&) noexcept = default;

		unsigned Size() const noexcept;
		const std::string SupportedCharacters() const noexcept;

		Texture2D* GetTexture() const noexcept;

		std::optional<Glyph> GetCharGlyph(char chr) const noexcept;
		std::optional<Math::Rectangle> GetCharSourceRectangle(char chr) const noexcept;

		Reflection::UUID GetUUID() const noexcept override;
		const char* FileExtension() const noexcept override;

		~Font();

		friend struct Internal::AssetUUIDReader;
	};
}