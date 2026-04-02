#include "IPhysicsEngine.hpp"
#include "IPhysicsEngine.h"

using namespace Engine3DRadSpace::Physics;

void E3DRSP_IPhysicsEngine_Simulate(E3DRSP_IPhysicsEngine* physics, float dt)
{
	reinterpret_cast<IPhysicsEngine*>(physics)->Simulate(dt);
}

void* E3DRSP_IPhysicsEngine_GetScene(E3DRSP_IPhysicsEngine* physics)
{
	return reinterpret_cast<IPhysicsEngine*>(physics)->GetScene();
}