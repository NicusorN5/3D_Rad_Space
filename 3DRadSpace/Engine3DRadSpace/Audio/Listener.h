#pragma once
#include "../Math/Vector3.h"
#include "../Core/Libs.h"

typedef struct E3DRSP_Listener
{
	float Volume;
	E3DRSP_Vector3 Position;
	E3DRSP_Vector3 Velocity;

	E3DRSP_Vector3 Directio;
	E3DRSP_Vector3 Normal;

	_Bool Enabled;
} E3DRSP_Listener;