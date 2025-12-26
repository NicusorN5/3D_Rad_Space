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

#ifdef __cplusplus
extern "C"
{
#endif
E3DRSP_MATH_EXPORT _Bool E3DRSP_BoundingPlane_IntersectsBox(E3DRSP_BoundingPlane* plane, const E3DRSP_BoundingBox* box);
E3DRSP_MATH_EXPORT _Bool E3DRSP_BoundingPlane_IntersectsSphere(E3DRSP_BoundingPlane* plane, const E3DRSP_BoundingSphere* sphere);
E3DRSP_MATH_EXPORT _Bool E3DRSP_BoundingPlane_IntersectsRay(E3DRSP_BoundingPlane* plane, const E3DRSP_Ray* ray);

E3DRSP_MATH_EXPORT _Bool E3DRSP_BoundingPlane_ContainsPoint(E3DRSP_BoundingPlane* plane, const E3DRSP_Vector3* p);

#ifdef __cplusplus
}
#endif