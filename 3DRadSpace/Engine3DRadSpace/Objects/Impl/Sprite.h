#pragma once
#include "../IObject2D.hpp"
#include "../../Math/Color.h"

typedef void* E3DRSP_Sprite;
typedef void* E3DRSP_ITexture2D;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Sprite E3DRSP_Sprite_Create();

	E3DRSP_OBJECTS_IMPL_EXPORT bool E3DRSP_Sprite_GetFlipU(E3DRSP_Sprite sprite);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Sprite_SetFlipU(E3DRSP_Sprite sprite, bool flipU);

	E3DRSP_OBJECTS_IMPL_EXPORT bool E3DRSP_Sprite_GetFlipV(E3DRSP_Sprite sprite);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Sprite_SetFlipV(E3DRSP_Sprite sprite, bool flipV);

	E3DRSP_OBJECTS_IMPL_EXPORT unsigned E3DRSP_Sprite_GetTextureID(E3DRSP_Sprite sprite);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Sprite_SetTextureID(E3DRSP_Sprite sprite, unsigned id);

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_ITexture2D E3DRSP_Sprite_GetTexture(E3DRSP_Sprite sprite);

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Color E3DRSP_Sprite_GetTintColor(E3DRSP_Sprite sprite);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_Sprite_SetTintColor(E3DRSP_Sprite sprite, const E3DRSP_Color *color);
#ifdef __cplusplus
}
#endif