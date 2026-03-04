#include "IStaticCollider.hpp"

using namespace Engine3DRadSpace::Physics;

IStaticCollider::IStaticCollider(IPhysicsEngine* physics) : ICollider(physics),
	LinearDamping(this),
	StaticFriction(this),
	DynamicFriction(this),
	Restitution(this)
{
}