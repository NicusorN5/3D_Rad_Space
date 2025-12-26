#pragma once
#include "Vector3.h"

typedef struct E3DRSP_BoundingBox
{
	E3DRSP_Vector3 Position;
	E3DRSP_Vector3 Scale;
} E3DRSP_BoundingBox;

struct E3DRSP_BoundingSphere;
struct E3DRSP_BoundingPlane;
struct E3DRSP_Ray;

#ifdef __cplusplus
extern "C"
{
#endif	
	E3DRSP_Vector3 E3DRSP_BoundingBox_Min(E3DRSP_BoundingBox* box);
	E3DRSP_Vector3 E3DRSP_BoundingBox_Center(E3DRSP_BoundingBox* box);
	E3DRSP_Vector3 E3DRSP_BoundingBox_Max(E3DRSP_BoundingBox* box);

	_Bool E3DRSP_BoundingBox_IntersectsBox(E3DRSP_BoundingBox* box1, const E3DRSP_BoundingBox *box2);
	_Bool E3DRSP_BoundingBox_IntersectsSphere(E3DRSP_BoundingBox* box, const E3DRSP_BoundingSphere *sphere);
	_Bool E3DRSP_BoundingBox_IntersectsPlane(E3DRSP_BoundingBox* box, const E3DRSP_BoundingPlane *plane);
	_Bool E3DRSP_BoundingBox_IntersectsRay(E3DRSP_BoundingBox* box, const E3DRSP_Ray *ray);

	_Bool E3DRSP_BoundingBox_ContainsPoint(E3DRSP_BoundingBox* box, const E3DRSP_Vector3* point);

	E3DRSP_Vector3 E3DRSP_BoundingBox_GetCorner(E3DRSP_BoundingBox* box, int index);
#ifdef __cplusplus
}
#endif