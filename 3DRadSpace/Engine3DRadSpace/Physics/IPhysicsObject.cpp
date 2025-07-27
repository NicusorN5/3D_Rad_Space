#include "IPhysicsObject.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;

IPhysicsObject::IPhysicsObject():
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