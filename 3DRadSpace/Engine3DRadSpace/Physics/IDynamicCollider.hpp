#pragma once
#include "IStaticCollider.hpp"

namespace Engine3DRadSpace::Physics
{
	class E3DRSP_PHYSICS_EXPORT IDynamicCollider: public IStaticCollider
	{
	protected:
		float _angularDamping = 0;
		virtual float _getAngularDamping() = 0;
		virtual void _setAngularDamping(float angularDamping) = 0;

		Math::Vector3 _linearVelocity;
		virtual Math::Vector3 _getLinearVelocity() = 0;
		virtual void _setLinearVelocity(const Math::Vector3& linearVelocity) = 0;

		Math::Vector3 _angularVelocity;
		virtual Math::Vector3 _getAngularVelocity() = 0;
		virtual void _setAngularVelocity(const Math::Vector3& linearVelocity) = 0;

		Math::Vector3 _maxAngularVelocity;
		virtual Math::Vector3 _getMaxAngularVelocity() = 0;
		virtual void _setMaxAngularVelocity(const Math::Vector3& linearVelocity) = 0;

		IDynamicCollider(IPhysicsEngine* physics);
	public:
		GetSet<float, ICollider, &_getAngularDamping, &_setAngularDamping> AngularDamping;
		GetSet<Math::Vector3, ICollider, &_getLinearVelocity, &_setLinearVelocity> LinearVelocity;
		GetSet<Math::Vector3, ICollider, &_getAngularVelocity, &_setAngularVelocity> AngularVelocity;
		GetSet<Math::Vector3, ICollider, &_getMaxAngularVelocity, &_setMaxAngularVelocity> MaxAngularVelocity;

		virtual bool ApplyForce(const Math::Vector3& force) = 0;
		virtual bool ApplyForce(const Math::Vector3& force, const Math::Vector3& center) = 0;
		virtual bool ApplyTorque(const Math::Vector3& force) = 0;

		virtual bool ApplyAcceleration(const Math::Vector3& acc) = 0;
		virtual bool ApplyAngularAcceleration(const Math::Vector3& acc) = 0;
	};
}