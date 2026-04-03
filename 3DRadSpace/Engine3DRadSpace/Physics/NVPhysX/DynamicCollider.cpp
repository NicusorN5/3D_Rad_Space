#include "DynamicCollider.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::NVPhysX;

DynamicCollider::DynamicCollider(IPhysicsEngine* physics) : IDynamicCollider(physics)
{
}

float DynamicCollider::_getMass()
{
	return 0.0f;
}

void DynamicCollider::_setMass(float mass)
{
}

float DynamicCollider::_getLinearDamping()
{
	return 0.0f;
}

void DynamicCollider::_setLinearDamping(float linearDamping)
{
}

float DynamicCollider::_getAngularDamping()
{
	return 0.0f;
}

void DynamicCollider::_setAngularDamping(float angularDamping)
{
}

float DynamicCollider::_getStaticFriction()
{
	return 0.0f;
}

void DynamicCollider::_setStaticFriction(float friction)
{
}

float DynamicCollider::_getDynamicFriction()
{
	return 0.0f;
}

void DynamicCollider::_setDynamicFriction(float friction)
{
}

float DynamicCollider::_getRestitution()
{
	return 0.0f;
}

void DynamicCollider::_setRestitution(float restitution)
{
}

Math::Vector3 DynamicCollider::_getLinearVelocity()
{
	return Math::Vector3();
}

void DynamicCollider::_setLinearVelocity(const Math::Vector3 & linearVelocity)
{
}

Vector3 DynamicCollider::_getAngularVelocity()
{
	return Math::Vector3();
}

void DynamicCollider::_setAngularVelocity(const Math::Vector3 & linearVelocity)
{
}

Vector3 DynamicCollider::_getMaxAngularVelocity()
{
	return Math::Vector3();
}

void DynamicCollider::_setMaxAngularVelocity(const Math::Vector3 & linearVelocity)
{
}

bool DynamicCollider::ApplyForce(const Math::Vector3 & force)
{
	return false;
}

bool DynamicCollider::ApplyForce(const Math::Vector3 & force, const Math::Vector3 & center)
{
	return false;
}

bool DynamicCollider::ApplyTorque(const Math::Vector3 & force)
{
	return false;
}

bool DynamicCollider::ApplyAcceleration(const Math::Vector3 & acc)
{
	return false;
}

bool DynamicCollider::ApplyAngularAcceleration(const Math::Vector3 & acc)
{
	return false;
}

void DynamicCollider::UpdateTransform()
{

}

void DynamicCollider::UpdateTransform(const Math::Vector3 & position, const Math::Quaternion & rotation)
{
}

std::optional<float> DynamicCollider::Intersects(const Math::Ray& r)
{
	return 0.0f;
}