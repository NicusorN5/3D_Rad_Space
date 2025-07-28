#include "IPhysicsObject.hpp"
#include "../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;

IPhysicsObject::IPhysicsObject():
	_physics(nullptr),
	Mass(this),
	LinearDamping(this),
	AngularDamping(this),
	StaticFriction(this),
	DynamicFriction(this),
	Restitution(this),
	LinearVelocity(this),
	AngularVelocity(this),
	MaxAngularVelocity(this)
{
}

void IPhysicsObject::Initialize()
{
	_physics = _game->Physics.get();
}

PhysicsEngine* IPhysicsObject::GetPhysics() const noexcept
{
	return _physics;
}