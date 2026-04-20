#include "ICollider.hpp"
#include "IPhysicsEngine.hpp"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;

ICollider::ICollider(IPhysicsEngine* physics) :
	_physics(physics)
{
}

IPhysicsEngine* ICollider::GetPhysics() const noexcept
{
	return _physics;
}