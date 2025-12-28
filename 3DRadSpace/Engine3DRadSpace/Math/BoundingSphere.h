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

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_MATH_EXPORT bool E3DRSP_BoundingSphere_IntersectsBox(E3DRSP_BoundingSphere* sphere, const E3DRSP_BoundingBox* box);
	E3DRSP_MATH_EXPORT bool E3DRSP_BoundingSphere_IntersectsSphere(E3DRSP_BoundingSphere* sphere1, const E3DRSP_BoundingSphere* sphere2);
	E3DRSP_MATH_EXPORT bool E3DRSP_BoundingSphere_IntersectsPlane(E3DRSP_BoundingSphere* sphere, const E3DRSP_BoundingPlane* plane);
	E3DRSP_MATH_EXPORT bool E3DRSP_BoundingSphere_ContainsPoint(E3DRSP_BoundingSphere* sphere, const E3DRSP_Vector3* point);
#ifdef __cplusplus
}
#endif