#include "DynamicRigidbody.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::NVPhysX;

DynamicRigidbody::DynamicRigidbody(IPhysicsEngine* physics) : ICollider(physics)
{
}

float DynamicRigidbody::_getMass()
{
	return 0.0f;
}

void DynamicRigidbody::_setMass(float mass)
{
}

float DynamicRigidbody::_getLinearDamping()
{
	return 0.0f;
}

void DynamicRigidbody::_setLinearDamping(float linearDamping)
{
}

float DynamicRigidbody::_getAngularDamping()
{
	return 0.0f;
}

void DynamicRigidbody::_setAngularDamping(float angularDamping)
{
}

float DynamicRigidbody::_getStaticFriction()
{
	return 0.0f;
}

void DynamicRigidbody::_setStaticFriction(float friction)
{
}

float DynamicRigidbody::_getDynamicFriction()
{
	return 0.0f;
}

void DynamicRigidbody::_setDynamicFriction(float friction)
{
}

float DynamicRigidbody::_getRestitution()
{
	return 0.0f;
}

void DynamicRigidbody::_setRestitution(float restitution)
{
}

Math::Vector3 DynamicRigidbody::_getLinearVelocity()
{
	return Math::Vector3();
}

void DynamicRigidbody::_setLinearVelocity(const Math::Vector3 & linearVelocity)
{
}

Vector3 DynamicRigidbody::_getAngularVelocity()
{
	return Math::Vector3();
}

void DynamicRigidbody::_setAngularVelocity(const Math::Vector3 & linearVelocity)
{
}

Vector3 DynamicRigidbody::_getMaxAngularVelocity()
{
	return Math::Vector3();
}

void DynamicRigidbody::_setMaxAngularVelocity(const Math::Vector3 & linearVelocity)
{
}

bool DynamicRigidbody::ApplyForce(const Math::Vector3 & force)
{
	return false;
}

bool DynamicRigidbody::ApplyForce(const Math::Vector3 & force, const Math::Vector3 & center)
{
	return false;
}

bool DynamicRigidbody::ApplyTorque(const Math::Vector3 & force)
{
	return false;
}

bool DynamicRigidbody::ApplyAcceleration(const Math::Vector3 & acc)
{
	return false;
}

bool DynamicRigidbody::ApplyAngularAcceleration(const Math::Vector3 & acc)
{
	return false;
}

void DynamicRigidbody::Update()
{

}

std::optional<float> DynamicRigidbody::Intersects(const Math::Ray& r)
{
	return 0.0f;
}