#include "DynamicRigidbody.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;

void DynamicRigidbody::Update()
{
}

void DynamicRigidbody::Load()
{
}

void DynamicRigidbody::Load(const std::filesystem::path & path)
{
}

Reflection::UUID DynamicRigidbody::GetUUID() const noexcept
{
	// {48E6C1B9-2ECA-4C54-A307-FEA05B0B03E4}
	return {0x48e6c1b9, 0x2eca, 0x4c54, { 0xa3, 0x7, 0xfe, 0xa0, 0x5b, 0xb, 0x3, 0xe4 }};
}

IGizmo* DynamicRigidbody::GetGizmo() const noexcept
{
	return nullptr;
}

void DynamicRigidbody::Draw3D()
{
}

std::optional<float> DynamicRigidbody::Intersects(const Math::Ray & r)
{
	return std::optional<float>();
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
