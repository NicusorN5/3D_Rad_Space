#include "ICollider.h"
#include "../../Objects/Impl/ICollider.hpp"

using namespace Engine3DRadSpace::Physicsl

float E3DRSP_ICollider_GetMass(E3DRSP_ICollider* collider)
{
	return reinterpret_cast<ICollider*>(collider)->Mass;
}

void E3DRSP_ICollider_SetMass(E3DRSP_ICollider* collider, float mass)
{
	reinterpret_cast<ICollider*>(collider)->Mass = mass;
}

E3DRSP_IPhysicsEngine E3DRSP_ICollider_GetPhysics(const E3DRSP_ICollider* collider)
{
	return reinterpret_cast<const ICollider*>(collider)->GetPhysics();
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

void E3DRSP_ICollider_Destroy(E3DRSP_ICollider* collider)
{
	delete reinterpret_cast<ICollider*>(collider);
}