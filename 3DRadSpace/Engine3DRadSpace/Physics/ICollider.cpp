#include "ICollider.hpp"
#include "IPhysicsEngine.hpp"

using namespace Engine3DRadSpace::Physics;

ICollider::ICollider(IPhysicsEngine* physics) :
	_physics(physics),
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