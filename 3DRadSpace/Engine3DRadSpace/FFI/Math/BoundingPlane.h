#pragma once
#include "Vector3.h"

struct E3DRSP_BoundingBox;
struct E3DRSP_BoundingSphere;
struct E3DRSP_Ray;

typedef struct E3DRSP_BoundingPlane
{
	E3DRSP_Vector3 Normal;
	float D;
} E3DRSP_BoundingPlane;