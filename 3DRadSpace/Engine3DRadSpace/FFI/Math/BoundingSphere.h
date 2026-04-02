#pragma once
#include "Vector3.h"

struct E3DRSP_BoundingBox;
struct E3DRSP_BoundingPlane;
struct E3DRSP_Ray;

typedef struct E3DRSP_BoundingSphere
{
	E3DRSP_Vector3 Center;
	float Radius;
} E3DRSP_BoundingSphere;