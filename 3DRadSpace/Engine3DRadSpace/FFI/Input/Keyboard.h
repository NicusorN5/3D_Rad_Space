#pragma once
#include "../Core/Libs.h"
#include "Key.h"
#include "KeyState.h"

typedef struct E3DRSP_Keyboard
{
	uint8_t Keys[10];
} E3DRSP_Keyboard;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_INPUT_EXPORT bool E3DRSP_Keyboard_IsKeyDown(E3DRSP_Keyboard* kb, E3DRSP_Key key);
	E3DRSP_INPUT_EXPORT bool E3DRSP_Keyboard_IsKeyUp(E3DRSP_Keyboard* kb, E3DRSP_Key key);
	E3DRSP_INPUT_EXPORT bool E3DRSP_Keyboard_IsAnyKeyDown(E3DRSP_Keyboard *kb);
	E3DRSP_INPUT_EXPORT E3DRSP_KeyState E3DRSP_Keyboard_At(E3DRSP_Keyboard* kb, E3DRSP_Key key);
#ifdef __cplusplus
}
#endif