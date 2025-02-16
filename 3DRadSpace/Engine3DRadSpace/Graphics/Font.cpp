/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/Font.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "Font.hpp"
#include "PixelFormat.hpp"
#include "../Logging/Exception.hpp"
#include "Texture2D.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace;

FT_Library FreeTypeLib;

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
	_font = new FT_Face();
	auto font = *static_cast<FT_Face*>(_font);

	if(FT_New_Face(FreeTypeLib, path.string().c_str(), 0, &font))
	{
		throw Exception("Failed to load font " + path.string()  + " !");
	}

	FT_Set_Pixel_Sizes(font, 0, size);

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

	//Precomputate a font texture atlas size. Using a naive implementation.

	//Initial allocated size.
	unsigned atlasX = 256;
	unsigned atlasY = 256;

	unsigned currentX = 0;
	unsigned currentY = 0;

	unsigned boundaryY = 0;

	bool finished = false;

fontSizeComputation:
	while (!finished)
	{
		for (auto c : _supportedCharacters)
		{
			if (FT_Load_Char(font, c, FT_LOAD_COMPUTE_METRICS))
				continue;

			auto w = font->glyph->bitmap.width;
			auto h = font->glyph->bitmap.rows;

			auto glyph = Glyph
			{
				.Character = c,
				.Size = Point{static_cast<int>(w), static_cast<int>(h)},
				.Bearing = Point{font->glyph->bitmap_left, font->glyph->bitmap_top},
				.Advance = static_cast<unsigned>(font->glyph->advance.x)
			};

			_glyphs.emplace_back(glyph, Math::Rectangle(currentX, currentY, w, h));

			currentX += w;
			boundaryY = std::max(boundaryY, h);

			//move to new line
			if (currentX >= atlasX)
			{
				currentX = 0;
				currentY += boundaryY;

				//if image size is exceeded, resize and then recalculate the atlas.
				if (currentY >= atlasY)
				{
					atlasX *= 2;
					atlasY *= 2;

					_glyphs.clear();
					goto fontSizeComputation;
				}
			}
		}

		atlasY = currentY + boundaryY;
		finished = true;
	}

	std::unique_ptr<Color[]> fontAtlas = std::make_unique<Color[]>(atlasX * atlasY);

	for(auto &[glyph, rc] : _glyphs)
	{
		if (FT_Load_Char(font, glyph.Character, FT_LOAD_RENDER))
			continue;

		using std::ranges::views::iota;

		for (auto x : iota(0, glyph.Size.X))
		{
			for (auto y : iota(0, glyph.Size.Y))
			{
				auto index1 = (atlasX * (y + rc.Y)) + x + rc.X;
				auto index2 = (rc.Width * y) + x;

				auto alpha = static_cast<float>(font->glyph->bitmap.buffer[index2]) / 255.0f;
				
				fontAtlas[index1] = Color(alpha, alpha, alpha, alpha);
			}
		}
	}

	_texture = std::make_unique<Texture2D>(_device, static_cast<void*>(fontAtlas.get()), atlasX, atlasY, PixelFormat::R32G32B32A32_Float);

	_valid = true;
}

Font::Font(GraphicsDevice* device, const std::filesystem::path& path) : Font(device, path, 14, nullptr)
{
}

Font::Font(Font&& font) noexcept :
	_valid(font._valid),
	_font(font._font),
	_device(font._device),
	_size(font._size),
	_supportedCharacters(std::move(font._supportedCharacters)),
	_glyphs(std::move(font._glyphs)),
	_texture(std::move(font._texture))
{
	font._valid = false;
	font._font = nullptr;
}

Font::Font(Internal::AssetUUIDReader dummy) :
	_valid(false),
	_font{},
	_device(nullptr),
	_size(0)
{
	(void)dummy;
}

Font& Font::operator=(Font&& font) noexcept
{
	if(this != &font)
	{
		_valid = font._valid;
		_font = font._font;
		_device = font._device;
		_size = font._size;
		_supportedCharacters = std::move(font._supportedCharacters);
		_glyphs = std::move(font._glyphs);
		_texture = std::move(font._texture);
		font._valid = false;
		font._font = nullptr;
	}
	return *this;
}

unsigned Font::Size() const noexcept
{
	return _size;
}

const std::string Font::SupportedCharacters() const noexcept
{
	return _supportedCharacters;
}

Texture2D* Font::GetTexture() const noexcept
{
	return _texture.get();
}

Font::~Font()
{
	if (_valid)
	{
		FT_Done_Face(*static_cast<FT_Face*>(_font));
		_valid = false;
	}
}

std::optional<Glyph> Font::GetCharGlyph(char chr) const noexcept
{
	for (auto& [glyph, _] : _glyphs)
	{
		if (glyph.Character == chr)
			return std::make_optional<Glyph>(glyph);
	}
	return std::nullopt;
}

std::optional<Math::Rectangle> Engine3DRadSpace::Graphics::Font::GetCharSourceRectangle(char chr) const noexcept
{
	for (auto& [glyph, rectangle] : _glyphs)
	{
		if (glyph.Character == chr)
			return std::make_optional<Math::Rectangle>(rectangle);
	}
	return std::nullopt;
}

Reflection::UUID Font::GetUUID() const noexcept
{
	// {7A9DEE1F-A3DE-4E55-B4D8-EC1BFE173B86}
	return { 0x7a9dee1f, 0xa3de, 0x4e55, { 0xb4, 0xd8, 0xec, 0x1b, 0xfe, 0x17, 0x3b, 0x86 } };
}

const char* Font::FileExtension() const noexcept
{
	return "TrueType Font (*.ttf)\0*.ttf\0All Files(*.*)\0*.*\0\0";
}
