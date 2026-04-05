#pragma once
#include "ICollider.hpp"

namespace Engine3DRadSpace::Physics
{
	class E3DRSP_PHYSICS_EXPORT IStaticCollider : public ICollider
	{
	protected:
		IStaticCollider(IPhysicsEngine* physics);
	
		float _linearDamping;
		virtual float _getLinearDamping() = 0;
		virtual void _setLinearDamping(float linearDamping) = 0;

		float _staticFriction;
		virtual float _getStaticFriction() = 0;
		virtual void _setStaticFriction(float friction) = 0;

		float _dynamicFriction;
		virtual float _getDynamicFriction() = 0;
		virtual void _setDynamicFriction(float friction) = 0;

		float _restitution;
		virtual float _getRestitution() = 0;
		virtual void _setRestitution(float restitution) = 0;
	public:
		GetSet<float, IStaticCollider, &_getLinearDamping, &_setLinearDamping> LinearDamping;
		GetSet<float, IStaticCollider, &_getStaticFriction, &_setStaticFriction> StaticFriction;
		GetSet<float, IStaticCollider, &_getDynamicFriction, &_setDynamicFriction> DynamicFriction;
		GetSet<float, IStaticCollider, &_getRestitution, &_setRestitution> Restitution;
	};
}