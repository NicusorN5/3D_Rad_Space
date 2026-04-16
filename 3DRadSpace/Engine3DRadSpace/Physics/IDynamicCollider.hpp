#pragma once
#include "IStaticCollider.hpp"
#include "../Math/Quaternion.hpp"

namespace Engine3DRadSpace::Physics
{
	class E3DRSP_PHYSICS_EXPORT IDynamicCollider: public IStaticCollider
	{
	protected:
		float _angularDamping = 0;
		virtual float _getAngularDamping() const = 0;
		virtual void _setAngularDamping(float angularDamping) = 0;

		Math::Vector3 _linearVelocity = Math::Vector3::Zero();
		virtual Math::Vector3 _getLinearVelocity() const = 0;
		virtual void _setLinearVelocity(const Math::Vector3& linearVelocity) = 0;

		Math::Vector3 _angularVelocity = Math::Vector3::Zero();
		virtual Math::Vector3 _getAngularVelocity() const = 0;
		virtual void _setAngularVelocity(const Math::Vector3& linearVelocity) = 0;

		Math::Vector3 _maxAngularVelocity = Math::Vector3(100.0f, 100.0f, 100.0f);
		virtual Math::Vector3 _getMaxAngularVelocity() const = 0;
		virtual void _setMaxAngularVelocity(const Math::Vector3& linearVelocity) = 0;

		IDynamicCollider(IPhysicsEngine* physics);
	public:
		GetSet<float, IDynamicCollider, &_getAngularDamping, &_setAngularDamping> AngularDamping;
		GetSet<Math::Vector3, IDynamicCollider, &_getLinearVelocity, &_setLinearVelocity> LinearVelocity;
		GetSet<Math::Vector3, IDynamicCollider, &_getAngularVelocity, &_setAngularVelocity> AngularVelocity;
		GetSet<Math::Vector3, IDynamicCollider, &_getMaxAngularVelocity, &_setMaxAngularVelocity> MaxAngularVelocity;

		virtual void AttachShape(const Math::BoundingBox& box) = 0;
		virtual void AttachShape(const Math::BoundingSphere& sphere) = 0;

		virtual void ApplyForce(const Math::Vector3& force) = 0;
		virtual void ApplyForce(const Math::Vector3& force, const Math::Vector3& center) = 0;
		virtual void ApplyTorque(const Math::Vector3& force) = 0;

		virtual void ApplyAcceleration(const Math::Vector3& acc) = 0;
		virtual void ApplyAngularAcceleration(const Math::Vector3& acc) = 0;

		virtual void SetKinematic(bool isKinematic) = 0;
	};
}