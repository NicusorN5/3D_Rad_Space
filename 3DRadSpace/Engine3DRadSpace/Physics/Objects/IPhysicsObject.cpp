#include "IPhysicsObject.hpp"
#include "../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::Objects;

IPhysicsObject::IPhysicsObject(IPhysicsEngine* physics) : _physics(physics)
{
}

void IPhysicsObject::Initialize()
{
	_physics = static_cast<IPhysicsEngine*>(_game->RequireService(typeid(IPhysicsEngine)));
}