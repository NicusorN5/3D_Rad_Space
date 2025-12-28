#pragma once
#include "Glyph.h"
#include "IGraphicsDevice.h"
#include "ITexture2D.h"

typedef void* E3DRSP_Font;

#ifdef __cplusplus
extern "C"
{
#endif
	/// <summary>
	/// Constructs a Font type, with specified size and supported characters.
	/// </summary>
	/// <param name="device">Graphics device</param>
	/// <param name="path">TTF Font path.</param>
	/// <param name="size">Font size</param>
	/// <param name="supportedCharacters">A C-style string of supported characters.</param>
	E3DRSP_GRAPHICS_EXPORT E3DRSP_Font E3DRSP_Font_Create(E3DRSP_IGraphicsDevice* device, const char* path, unsigned size, const char* supportedCharacters);

	/// <summary>
	/// Returns the size the font was created with.
	/// </summary>
	/// <returns>Font size.</returns>
	E3DRSP_GRAPHICS_EXPORT unsigned E3DRSP_Font_Size(E3DRSP_Font font);
	/// <summary>
	/// Returns a copy of the supported characters.
	/// </summary>
	/// <returns></returns>
	E3DRSP_GRAPHICS_EXPORT const char* E3DRSP_Font_SupportedCharacters(E3DRSP_Font font);

	/// <summary>
	/// Returns the texture containing all glyphs.
	/// </summary>
	/// <returns></returns>
	E3DRSP_GRAPHICS_EXPORT E3DRSP_ITexture2D* E3DRSP_Font_GetTexture(E3DRSP_Font font);

	/// <summary>
	/// Gets the glyph of a specific character.
	/// </summary>
	/// <param name="chr">Character.</param>
	/// <returns>NULL if that character is not supported.</returns>
	E3DRSP_GRAPHICS_EXPORT E3DRSP_Glyph* E3DRSP_Font_GetCharGlyph(E3DRSP_Font font, char chr);
	/// <summary>
	/// Gets the source rectangle of a specified character.
	/// </summary>
	/// <param name="chr">Character.</param>
	/// <returns>NULL if that character is not supported.</returns>
	E3DRSP_GRAPHICS_EXPORT E3DRSP_Rectangle* E3DRSP_Font_GetCharSourceRectangle(E3DRSP_Font font, char chr);

	void E3DRSP_Font_Destroy(E3DRSP_Font font);
#ifdef __cplusplus
}
#endif