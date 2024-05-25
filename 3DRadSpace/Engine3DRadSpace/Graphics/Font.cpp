#include "Font.hpp"

#include "PixelFormat.hpp"
#include "../Logging/Exception.hpp"
#include "Texture2D.hpp"

using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace;

FT_Library Font::FontManager::FreeTypeLib;

Font::FontManager::FontManager()
{
	if (FT_Init_FreeType(&FreeTypeLib))
	{
		throw Exception("Failed to load the FreeType library!");
	}
}

Font::FontManager::~FontManager()
{
	FT_Done_FreeType(FreeTypeLib);
}

Font::FontManager Font::_manager;

Font::Font(GraphicsDevice* device, const std::filesystem::path& path, unsigned size, const char* supportedCharacters):
	_device(device),
	_size(size),
	_supportedCharacters(supportedCharacters != nullptr ? supportedCharacters : "")
{
	if(FT_New_Face(FontManager::FreeTypeLib, path.string().c_str(), 0, &_font))
	{
		throw Exception("Failed to load font " + path.string()  + " !");
	}

	FT_Set_Pixel_Sizes(_font, 0, size);

	if(supportedCharacters == nullptr)
	{
		char defaultSupportedCharacters[128] = {}; 
		const char offset = ' ';
		for (char i = offset; i < '~'; i++)
		{
			defaultSupportedCharacters[i - offset] = i;
		}
		_supportedCharacters = defaultSupportedCharacters;
	}

	for(auto c : _supportedCharacters)
	{
		if (FT_Load_Char(_font, c, FT_LOAD_RENDER) != 0)
			continue;

		auto width = _font->glyph->bitmap.width;
		auto height = _font->glyph->bitmap.rows;
		auto fontBitmapBuffer = _font->glyph->bitmap.buffer;

		auto glyph = Glyph
		{
			.Character = c,
			.Size = Point{static_cast<int>(width), static_cast<int>(height)},
			.Bearing = Point{_font->glyph->bitmap_left, _font->glyph->bitmap_top},
			.Advance = static_cast<unsigned>(_font->glyph->advance.x)
		};

		//TODO: Use a font "megatexture" instead of one texture for each character for performance reasons.
		[[likely]] if(fontBitmapBuffer != nullptr)
		{
			std::unique_ptr<Color[]> glyphBuffer = std::make_unique<Color[]>(size_t(width) * height);

			for (size_t j = 0; j < height; j++)
			{
				for (size_t i = 0; i < width; i++)
				{
					auto p = (j * width) + i;
					auto alpha = static_cast<float>(_font->glyph->bitmap.buffer[p]) / 255.0f;
					glyphBuffer[p] = Color(alpha, alpha, alpha, alpha);
				}
			}
			//TODO: Might want to change to R32, but it simply doesn't work.
			_characters.emplace_back(glyph, std::make_unique<Texture2D>(_device, glyphBuffer.get(), width, height, PixelFormat::R32G32B32A32_Float));
		}
		else
		{
			//create a transparent texture.
			std::array<Color, 4> transparentColors = { 0 };
			_characters.emplace_back(glyph, std::make_unique<Texture2D>(_device, transparentColors, 2, 2));
		}
	}
	_valid = true;
}

Font::Font(GraphicsDevice* device, const std::filesystem::path& path) : Font(device, path, 14, nullptr)
{
}

Font::Font(Internal::AssetUUIDReader dummy) :
	_valid(false),
	_font{},
	_device(nullptr),
	_size(0)
{
	(void)dummy;
}

unsigned Font::Size() const noexcept
{
	return _size;
}

const std::string Font::SupportedCharacters() const noexcept
{
	return _supportedCharacters;
}

Texture2D* Font::operator[](char chr) const noexcept
{
	for (auto& [glyph, ptr] : this->_characters)
	{
		if (glyph.Character == chr) 
 			return ptr.get();
	}
	return nullptr;
}

Font::~Font()
{
	if (_valid)
	{
		FT_Done_Face(_font);
		_valid = false;
	}
}

std::optional<Glyph> Font::GetCharGlyph(char chr) const noexcept
{
	for (auto& [glyph, ptr] : this->_characters)
	{
		if (glyph.Character == chr)
			return std::make_optional<Glyph>(glyph);
	}
	return std::nullopt;
}

Reflection::UUID Font::GetUUID() const noexcept
{
	// {7A9DEE1F-A3DE-4E55-B4D8-EC1BFE173B86}
	return { 0x7a9dee1f, 0xa3de, 0x4e55, { 0xb4, 0xd8, 0xec, 0x1b, 0xfe, 0x17, 0x3b, 0x86 } };
}
