#include "Sprite.h"
#include "../../../Objects/Impl/Sprite.hpp"

using namespace Engine3DRadSpace::Objects;

E3DRSP_Sprite E3DRSP_Sprite_Create()
{
	return new Sprite();
}

bool E3DRSP_Sprite_GetFlipU(E3DRSP_Sprite sprite)
{
	return static_cast<Sprite*>(sprite)->FlipU;
}
void E3DRSP_Sprite_SetFlipU(E3DRSP_Sprite sprite, bool flipU)
{
	static_cast<Sprite*>(sprite)->FlipU = flipU;
}

bool E3DRSP_Sprite_GetFlipV(E3DRSP_Sprite sprite)
{
	return static_cast<Sprite*>(sprite)->FlipV;
}

void E3DRSP_Sprite_SetFlipV(E3DRSP_Sprite sprite, bool flipV)
{
	static_cast<Sprite*>(sprite)->FlipV = flipV;
}

unsigned E3DRSP_Sprite_GetTextureID(E3DRSP_Sprite sprite)
{
	return static_cast<Sprite*>(sprite)->Image;
}

void E3DRSP_Sprite_SetTextureID(E3DRSP_Sprite sprite, unsigned id)
{
	static_cast<Sprite*>(sprite)->Image = id;
}

E3DRSP_ITexture2D E3DRSP_Sprite_GetTexture(E3DRSP_Sprite sprite)
{
	return static_cast<Sprite*>(sprite)->GetSpriteImage();
}

E3DRSP_Color E3DRSP_Sprite_GetTintColor(E3DRSP_Sprite sprite)
{
	return std::bit_cast<E3DRSP_Color>(static_cast<Sprite*>(sprite)->TintColor);
}

void E3DRSP_Sprite_SetTintColor(E3DRSP_Sprite sprite, const E3DRSP_Color* color)
{
	static_cast<Sprite*>(sprite)->TintColor = std::bit_cast<Color>(*color);
}