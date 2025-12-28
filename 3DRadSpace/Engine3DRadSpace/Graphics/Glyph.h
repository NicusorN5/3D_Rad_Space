#pragma once
#include "../Math/Point.h"

typedef struct E3DRSP_Glyph
{
	char Character;
	E3DRSP_Point Size;
	E3DRSP_Point Bearing;
	unsigned Advance;
} E3DRSP_Glyph;