#pragma once
#include "../Core/Libs.h"
#include "ButtonState.h"
#include "../Math/Point.h"

typedef struct E3DRSP_Mouse
{
	E3DRSP_ButtonState LeftButton;
	E3DRSP_ButtonState MiddleButton;
	E3DRSP_ButtonState RightButton;

	E3DRSP_Point Position;
	float ScrollWheel;
};