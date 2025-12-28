#pragma once
#include "../Core/Libs.h"

typedef void* E3DRSP_IPhysicsEngine;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_PHYSICS_EXPORT void E3DRSP_IPhysicsEngine_Simulate(E3DRSP_IPhysicsEngine *physics, float dt);
	E3DRSP_PHYSICS_EXPORT void* E3DRSP_IPhysicsEngine_GetScene(E3DRSP_IPhysicsEngine *physics);
#ifdef __cplusplus
}
#endif