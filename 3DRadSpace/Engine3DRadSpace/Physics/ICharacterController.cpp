#include "ICharacterController.hpp"

using namespace Engine3DRadSpace::Physics;

ICharacterController::ICharacterController(IPhysicsEngine* physics) : ICollider(physics),
	Height(this),
	Radius(this),
	MaxSlopeAngle(this),
	Gravity(this)
{
}