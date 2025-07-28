#pragma once
#include "../Math/Vector3.h"
#include "../Core/Libs.h"

typedef struct E3DRSP_AudioSource
{
	float Pitch;

	float Gain;
	float MaxGain;
	float MinGain;

	E3DRSP_Vector3 Position;
	E3DRSP_Vector3 Velocity;
	E3DRSP_Vector3 Direction;

	float MaxDistance;
	float ReferenceDistance;

	float RolloffFactor;

	float ConeOuterGain;
	float ConeInnerAngle;
	float ConeOuterAngle;

	_Bool Looping;
} E3DRSP_AudioSource;