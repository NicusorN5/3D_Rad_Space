#include "FreeCam.h"
#include "../../../Objects/Impl/FreeCam.hpp"

using namespace Engine3DRadSpace::Objects;

E3DRSP_FreeCam E3DRSP_FreeCam_Create()
{
	return new FreeCam;
}

float E3DRSP_FreeCam_GetMovementSpeed(E3DRSP_FreeCam freecam)
{
	return static_cast<FreeCam*>(freecam)->MovementSpeed;
}

void E3DRSP_FreeCam_SetMovementSpeed(E3DRSP_FreeCam freecam, float speed)
{
	static_cast<FreeCam*>(freecam)->MovementSpeed = speed;
}

float E3DRSP_FreeCam_GetSensitivity(E3DRSP_FreeCam freecam)
{
	return static_cast<FreeCam*>(freecam)->Sensitivity;
}

void E3DRSP_FreeCam_SetSensitivity(E3DRSP_FreeCam freecam, float sensitivity)
{
	static_cast<FreeCam*>(freecam)->Sensitivity = sensitivity;
}

bool E3DRSP_FreeCam_IsXInverted(E3DRSP_FreeCam freecam)
{
	return static_cast<FreeCam*>(freecam)->InvertX;
}

void E3DRSP_FreeCam_SetXInverted(E3DRSP_FreeCam freecam, bool invertX)
{
	static_cast<FreeCam*>(freecam)->InvertX = invertX;
}

bool E3DRSP_FreeCam_IsYInverted(E3DRSP_FreeCam freecam)
{
	return static_cast<FreeCam*>(freecam)->InvertX;
}

void E3DRSP_FreeCam_SetYInverted(E3DRSP_FreeCam freecam, bool invertY)
{
	static_cast<FreeCam*>(freecam)->InvertY = invertY;
}

E3DRSP_Key E3DRSP_FreeCam_GetForwardKey(E3DRSP_FreeCam freecam)
{
	return static_cast<E3DRSP_Key>(static_cast<FreeCam*>(freecam)->Forward);
}

void E3DRSP_FreeCam_SetForwardKey(E3DRSP_FreeCam freecam, E3DRSP_Key key)
{
	static_cast<FreeCam*>(freecam)->Forward = static_cast<Input::Key>(key);
}

E3DRSP_Key E3DRSP_FreeCam_GetBackwardKey(E3DRSP_FreeCam freecam)
{
	return static_cast<E3DRSP_Key>(static_cast<FreeCam*>(freecam)->Backward);
}

void E3DRSP_FreeCam_SetBackwardKey(E3DRSP_FreeCam freecam, E3DRSP_Key key)
{
	static_cast<FreeCam*>(freecam)->Backward = static_cast<Input::Key>(key);
}

E3DRSP_Key E3DRSP_FreeCam_GetLeftKey(E3DRSP_FreeCam freecam)
{
	return static_cast<E3DRSP_Key>(static_cast<FreeCam*>(freecam)->Left);
}

void E3DRSP_FreeCam_SetLeftKey(E3DRSP_FreeCam freecam, E3DRSP_Key key)
{
	static_cast<FreeCam*>(freecam)->Left = static_cast<Input::Key>(key);
}

E3DRSP_Key E3DRSP_FreeCam_GetRightKey(E3DRSP_FreeCam freecam)
{
	return static_cast<E3DRSP_Key>(static_cast<FreeCam*>(freecam)->Right);
}
void E3DRSP_FreeCam_SetRightKey(E3DRSP_FreeCam freecam, E3DRSP_Key key)
{
	static_cast<FreeCam*>(freecam)->Right = static_cast<Input::Key>(key);
}