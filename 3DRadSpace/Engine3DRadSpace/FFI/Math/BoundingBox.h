#pragma once
#include "../Core/Libs.h"
#include "Vector3.h"

typedef struct E3DRSP_BoundingBox
{
	E3DRSP_Vector3 Position;
	E3DRSP_Vector3 Scale;
} E3DRSP_BoundingBox;

struct E3DRSP_BoundingSphere;
struct E3DRSP_BoundingPlane;
struct E3DRSP_Ray;