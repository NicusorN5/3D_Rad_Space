#pragma once
#include "../../Graphics/Glyph.hpp"
#include "../IAsset.hpp"
#include "../../GraphicsDevice.hpp"
#include "../../Internal/AssetUUIDReader.hpp"

namespace Engine3DRadSpace::Content::Assets
{
	/// <summary>
	/// Represents a Font.
	/// </summary>
	/// <remarks>
	/// Fonts are being loaded using FreeType.
	/// When loading fonts, a single texture is created containing all supported characters. The texture is trivially packed (in a left-right, up-down order).
	/// </remarks>
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
	
		std::vector<std::pair<Graphics::Glyph, Math::Rectangle>> _glyphs;
		std::unique_ptr<Graphics::Texture2D> _texture;
		unsigned _size;

		Font(Internal::AssetUUIDReader dummy);
	public:
		/// <summary>
		/// Constructs a Font type, with specified size and supported characters.
		/// </summary>
		/// <param name="device">Graphics device</param>
		/// <param name="path">TTF Font path.</param>
		/// <param name="size">Font size</param>
		/// <param name="supportedCharacters">A C-style string of supported characters.</param>
		Font(GraphicsDevice* device, const std::filesystem::path &path, unsigned size, const char* supportedCharacters = nullptr);
		/// <summary>
		/// Loads a TTF font.
		/// </summary>
		/// <param name="device">Graphics Device</param>
		/// <param name="path">TTF font file path</param>
		Font(GraphicsDevice* device, const std::filesystem::path &path);

		Font(const Font&) = delete;
		Font(Font&& font) noexcept;

		Font& operator=(const Font&) = delete;
		Font& operator=(Font&&) noexcept;

		/// <summary>
		/// Returns the size the font was created with.
		/// </summary>
		/// <returns>Font size.</returns>
		unsigned Size() const noexcept;
		/// <summary>
		/// Returns a copy of the supported characters.
		/// </summary>
		/// <returns></returns>
		const std::string SupportedCharacters() const noexcept;

		/// <summary>
		/// Returns the texture containing all glyphs.
		/// </summary>
		/// <returns></returns>
		Graphics::Texture2D* GetTexture() const noexcept;

		/// <summary>
		/// Gets the glyph of a specific character.
		/// </summary>
		/// <param name="chr">Character.</param>
		/// <returns>Nullopt if that character is not supported.</returns>
		std::optional<Graphics::Glyph> GetCharGlyph(char chr) const noexcept;
		/// <summary>
		/// Gets the source rectangle of a specified character.
		/// </summary>
		/// <param name="chr">Character.</param>
		/// <returns>Nullopt if that character is not supported.</returns>
		std::optional<Math::Rectangle> GetCharSourceRectangle(char chr) const noexcept;

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

		~Font();

		friend struct Internal::AssetUUIDReader;
	};
}