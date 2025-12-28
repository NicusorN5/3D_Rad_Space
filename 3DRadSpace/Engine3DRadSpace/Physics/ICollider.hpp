#pragma once
#include "../Math/Vector3.hpp"
#include "../Math/Ray.hpp"
#include "../Core/GetSet.hpp"
#include "../Core/IUpdateable.hpp"

namespace Engine3DRadSpace::Physics
{
	class IPhysicsEngine;

	class E3DRSP_PHYSICS_EXPORT ICollider : public IUpdateable
	{
	protected:
		IPhysicsEngine* _physics;

		float _mass = 0;
		virtual float _getMass() = 0;
		virtual void _setMass(float mass) = 0;

		float _linearDamping = 0;
		virtual float _getLinearDamping() = 0;
		virtual void _setLinearDamping(float linearDamping) = 0;

		float _angularDamping = 0;
		virtual float _getAngularDamping() = 0;
		virtual void _setAngularDamping(float angularDamping) = 0;

		float _staticFriction = 0;
		virtual float _getStaticFriction() = 0;
		virtual void _setStaticFriction(float friction) = 0;

		float _dynamicFriction = 0;
		virtual float _getDynamicFriction() = 0;
		virtual void _setDynamicFriction(float friction) = 0;

		float _restitution = 0;
		virtual float _getRestitution() = 0;
		virtual void _setRestitution(float restitution) = 0;

		Math::Vector3 _linearVelocity;
		virtual Math::Vector3 _getLinearVelocity() = 0;
		virtual void _setLinearVelocity(const Math::Vector3& linearVelocity) = 0;

		Math::Vector3 _angularVelocity;
		virtual Math::Vector3 _getAngularVelocity() = 0;
		virtual void _setAngularVelocity(const Math::Vector3& linearVelocity) = 0;

		Math::Vector3 _maxAngularVelocity;
		virtual Math::Vector3 _getMaxAngularVelocity() = 0;
		virtual void _setMaxAngularVelocity(const Math::Vector3& linearVelocity) = 0;

		ICollider(IPhysicsEngine* physics);
	public:
		GetSet<float, ICollider, &_getMass, &_setMass> Mass;
		GetSet<float, ICollider, &_getLinearDamping, &_setLinearDamping> LinearDamping;
		GetSet<float, ICollider, &_getAngularDamping, &_setAngularDamping> AngularDamping;
		GetSet<float, ICollider, &_getStaticFriction, &_setStaticFriction> StaticFriction;
		GetSet<float, ICollider, &_getDynamicFriction, &_setDynamicFriction> DynamicFriction;
		GetSet<float, ICollider, &_getRestitution, &_setRestitution> Restitution;
		GetSet<Math::Vector3, ICollider, &_getLinearVelocity, &_setLinearVelocity> LinearVelocity;
		GetSet<Math::Vector3, ICollider, &_getAngularVelocity, &_setAngularVelocity> AngularVelocity;
		GetSet<Math::Vector3, ICollider, &_getMaxAngularVelocity, &_setMaxAngularVelocity> MaxAngularVelocity;

		IPhysicsEngine* GetPhysics() const noexcept;

		virtual bool ApplyForce(const Math::Vector3& force) = 0;
		virtual bool ApplyForce(const Math::Vector3& force, const Math::Vector3& center) = 0;
		virtual bool ApplyTorque(const Math::Vector3& force) = 0;

		virtual bool ApplyAcceleration(const Math::Vector3& acc) = 0;
		virtual bool ApplyAngularAcceleration(const Math::Vector3& acc) = 0;

		virtual std::optional<float> Intersects(const Math::Ray& r) = 0;

		virtual ~ICollider() = default;
	};
}