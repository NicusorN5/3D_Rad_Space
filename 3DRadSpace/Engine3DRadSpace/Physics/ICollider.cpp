#include "ICollider.hpp"
#include "ICollider.h"
#include "IPhysicsEngine.hpp"

using namespace Engine3DRadSpace::Math;
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

IPhysicsEngine* ICollider::GetPhysics() const noexcept
{
	return _physics;
}

float E3DRSP_ICollider_GetMass(E3DRSP_ICollider* collider)
{
	return reinterpret_cast<ICollider*>(collider)->Mass;
}

void E3DRSP_ICollider_SetMass(E3DRSP_ICollider* collider, float mass)
{
	reinterpret_cast<ICollider*>(collider)->Mass = mass;
}

float E3DRSP_ICollider_GetLinearDamping(E3DRSP_ICollider* collider)
{
	return reinterpret_cast<ICollider*>(collider)->LinearDamping;
}

void E3DRSP_ICollider_SetLinearDamping(E3DRSP_ICollider* collider, float linearDamping)
{
	reinterpret_cast<ICollider*>(collider)->LinearDamping = linearDamping;
}

float E3DRSP_ICollider_GetAngularDamping(E3DRSP_ICollider* collider)
{
	return reinterpret_cast<ICollider*>(collider)->AngularDamping;
}

void E3DRSP_ICollider_SetAngularDamping(E3DRSP_ICollider* collider, float angularDamping)
{
	reinterpret_cast<ICollider*>(collider)->AngularDamping = angularDamping;
}

float E3DRSP_ICollider_GetStaticFriction(E3DRSP_ICollider* collider)
{
	return reinterpret_cast<ICollider*>(collider)->StaticFriction;
}

void E3DRSP_ICollider_SetStaticFriction(E3DRSP_ICollider* collider, float staticFriction)
{
	reinterpret_cast<ICollider*>(collider)->StaticFriction = staticFriction;
}

float E3DRSP_ICollider_GetDynamicFriction(E3DRSP_ICollider* collider)
{
	return reinterpret_cast<ICollider*>(collider)->DynamicFriction;
}

void E3DRSP_ICollider_SetDynamicFriction(E3DRSP_ICollider* collider, float dynFriction)
{
	reinterpret_cast<ICollider*>(collider)->DynamicFriction = dynFriction;
}

float E3DRSP_ICollider_GetRestitution(E3DRSP_ICollider* collider)
{
	return reinterpret_cast<ICollider*>(collider)->Restitution;
}

void E3DRSP_ICollider_SetRestitution(E3DRSP_ICollider* collider, float restitution)
{
	reinterpret_cast<ICollider*>(collider)->Restitution = restitution;
}

E3DRSP_Vector3 E3DRSP_ICollider_GetLinearVelocity(E3DRSP_ICollider* collider)
{
	Vector3 v = reinterpret_cast<ICollider*>(collider)->LinearVelocity;
	return { v.X, v.Y, v.Z };
}

void E3DRSP_ICollider_SetLinearVelocity(E3DRSP_ICollider* collider, const E3DRSP_Vector3* vel)
{
	reinterpret_cast<ICollider*>(collider)->LinearVelocity = Vector3(vel->X, vel->Y, vel->Z);
}

E3DRSP_Vector3 E3DRSP_ICollider_GetAngularVelocity(E3DRSP_ICollider* collider)
{
	Vector3 v = reinterpret_cast<ICollider*>(collider)->AngularVelocity;
	return { v.X, v.Y, v.Z };
}

void E3DRSP_ICollider_SetAngularVelocity(E3DRSP_ICollider* collider, const E3DRSP_Vector3* vel)
{
	reinterpret_cast<ICollider*>(collider)->AngularVelocity = Vector3(vel->X, vel->Y, vel->Z);
}

E3DRSP_Vector3 E3DRSP_ICollider_GetMaxAngularVelocity(E3DRSP_ICollider* collider)
{
	Vector3 v = reinterpret_cast<ICollider*>(collider)->MaxAngularVelocity;
	return { v.X, v.Y, v.Z };
}

void E3DRSP_ICollider_SetMaxAngularVelocity(E3DRSP_ICollider* collider, const E3DRSP_Vector3* vel)
{
	reinterpret_cast<ICollider*>(collider)->MaxAngularVelocity = Vector3(vel->X, vel->Y, vel->Z);
}

E3DRSP_IPhysicsEngine E3DRSP_ICollider_GetPhysics(const E3DRSP_ICollider* collider)
{
	return reinterpret_cast<const ICollider*>(collider)->GetPhysics();
}

bool E3DRSP_ICollider_ApplyForce(E3DRSP_ICollider* collider, const E3DRSP_Vector3* force)
{
	return reinterpret_cast<ICollider*>(collider)->ApplyForce(Vector3(force->X, force->Y, force->Z));
}

bool E3DRSP_ICollider_ApplyForce2(E3DRSP_ICollider* collider, const E3DRSP_Vector3* force, const E3DRSP_Vector3* center)
{
	return reinterpret_cast<ICollider*>(collider)->ApplyForce(Vector3(force->X, force->Y, force->Z));
}

bool E3DRSP_ICollider_ApplyTorque(E3DRSP_ICollider* collider, const E3DRSP_Vector3* force)
{
	return reinterpret_cast<ICollider*>(collider)->ApplyTorque(Vector3(force->X, force->Y, force->Z));
}

bool E3DRSP_ICollider_ApplyAcceleration(E3DRSP_ICollider* collider, E3DRSP_Vector3* acc)
{
	return reinterpret_cast<ICollider*>(collider)->ApplyAcceleration(Vector3(acc->X, acc->Y, acc->Z));
}

bool E3DRSP_ICollider_ApplyAngularAcceleration(E3DRSP_ICollider* collider, E3DRSP_Vector3* acc)
{
	return reinterpret_cast<ICollider*>(collider)->ApplyAngularAcceleration(Vector3(acc->X, acc->Y, acc->Z));
}

float E3DRSP_ICollider_Intersects(E3DRSP_ICollider* collider, const E3DRSP_Ray* r)
{
	auto dst = reinterpret_cast<ICollider*>(collider)->Intersects(
		Ray
		{
			.Origin = {r->Origin.X, r->Origin.Y, r->Origin.Z},
			.Direction = {r->Direction.X, r->Direction.Y, r->Direction.Z}
		}
	);

	return dst.has_value() ? dst.value() : std::numeric_limits<float>::signaling_NaN();
}