#include "Font.h"
#include "../../Graphics/Font.hpp"
#include "../../Logging/AssetLoadingError.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

E3DRSP_Font E3DRSP_Font_Create(E3DRSP_IGraphicsDevice* device, const char* path, unsigned size, const char* supportedCharacters)
{
	try
	{
		auto font = new Font(
			reinterpret_cast<IGraphicsDevice*>(device),
			std::filesystem::path(path),
			size,
			supportedCharacters
		);

		return static_cast<E3DRSP_Font>(font);
	}
	catch(const Logging::AssetLoadingError& e)
	{
		return nullptr;
	}
}

unsigned E3DRSP_Font_Size(E3DRSP_Font font)
{
	return static_cast<Font*>(font)->Size();
}

const char* E3DRSP_Font_SupportedCharacters(E3DRSP_Font font)
{
	return static_cast<Font*>(font)->SupportedCharacters().c_str();
}

E3DRSP_ITexture2D* E3DRSP_Font_GetTexture(E3DRSP_Font font)
{
	return reinterpret_cast<E3DRSP_ITexture2D*>(static_cast<Font*>(font)->GetTexture());
}

E3DRSP_Glyph* E3DRSP_Font_GetCharGlyph(E3DRSP_Font font, char chr)
{
	auto glyphOpt = static_cast<Font*>(font)->GetCharGlyph(chr);
	if(glyphOpt.has_value())
	{
		auto glyph = glyphOpt.value();

		E3DRSP_Glyph* outGlyph = new E3DRSP_Glyph
		{
			glyph.Character,
			{ glyph.Size.X, glyph.Size.Y },
			{ glyph.Bearing.X, glyph.Bearing.Y },
			glyph.Advance
		};
		return outGlyph;
	}
	return nullptr;
}

E3DRSP_Rectangle* E3DRSP_Font_GetCharSourceRectangle(E3DRSP_Font font, char chr)
{
	auto rectOpt = static_cast<Font*>(font)->GetCharSourceRectangle(chr);
	if(rectOpt.has_value())
	{
		auto rect = new E3DRSP_Rectangle
		{
			rectOpt->X,
			rectOpt->Y,
			rectOpt->Width,
			rectOpt->Height
		};
		return rect;
	}
	return nullptr;
}

void E3DRSP_Font_Destroy(E3DRSP_Font font)
{
	delete static_cast<Font*>(font);
}