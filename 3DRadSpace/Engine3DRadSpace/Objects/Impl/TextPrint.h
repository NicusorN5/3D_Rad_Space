#pragma once
#include "../IObject2D.h"

typedef void* E3DRSP_TextPrint;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_TextPrint E3DRSP_TextPrint_Create();

	E3DRSP_OBJECTS_IMPL_EXPORT unsigned E3DRSP_TextPrint_GetFontID(E3DRSP_TextPrint textPrint);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_TextPrint_SetFontID(E3DRSP_TextPrint textPrint, unsigned id);

	E3DRSP_OBJECTS_IMPL_EXPORT E3DRSP_Color E3DRSP_TextPrint_GetColor(E3DRSP_TextPrint textPrint);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_TextPrint_SetColor(E3DRSP_TextPrint textPrint, const E3DRSP_Color *color);

	E3DRSP_OBJECTS_IMPL_EXPORT const char* E3DRSP_TextPrint_GetText(E3DRSP_TextPrint textPrint);
	E3DRSP_OBJECTS_IMPL_EXPORT void E3DRSP_TextPrint_SetText(E3DRSP_TextPrint textPrint, const char* text);
#ifdef __cplusplus
}
#endif