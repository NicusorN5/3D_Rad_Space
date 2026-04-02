#include "TextPrint.h"
#include "../../../Objects/Impl/TextPrint.hpp"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

E3DRSP_TextPrint E3DRSP_TextPrint_Create()
{
    return new TextPrint();
}

unsigned E3DRSP_TextPrint_GetFontID(E3DRSP_TextPrint textPrint)
{
    return static_cast<TextPrint*>(textPrint)->Font.ID;
}

void E3DRSP_TextPrint_SetFontID(E3DRSP_TextPrint textPrint, unsigned id)
{
    static_cast<TextPrint*>(textPrint)->Font = id;
}

E3DRSP_Color E3DRSP_TextPrint_GetColor(E3DRSP_TextPrint textPrint)
{
    return std::bit_cast<E3DRSP_Color>(static_cast<TextPrint*>(textPrint)->Colour);
}

void E3DRSP_TextPrint_SetColor(E3DRSP_TextPrint textPrint, const E3DRSP_Color* color)
{
    static_cast<TextPrint*>(textPrint)->Colour = std::bit_cast<Color>(*color);
}

const char* E3DRSP_TextPrint_GetText(E3DRSP_TextPrint textPrint)
{
    return static_cast<TextPrint*>(textPrint)->Text.c_str();
}

void E3DRSP_TextPrint_SetText(E3DRSP_TextPrint textPrint, const char* text)
{
    static_cast<TextPrint*>(textPrint)->Text = text;
}