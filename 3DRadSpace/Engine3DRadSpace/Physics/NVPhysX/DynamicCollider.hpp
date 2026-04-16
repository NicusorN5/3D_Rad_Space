#pragma once
#include "../IDynamicCollider.hpp"
#include "../Math/Quaternion.hpp"
#include <PxRigidDynamic.h>
#include <PxPhysics.h>
#include "PxUptr.hpp"

namespace Engine3DRadSpace::Physics::NVPhysX
{
	class E3DRSP_PHYSICS_OBJ_EXPORT DynamicCollider : public IDynamicCollider
	{
	protected:
		void _generateRigidbody();

		float _getMass() const override;
		void _setMass(float mass) override;

		float _getLinearDamping() const override;
		void _setLinearDamping(float linearDamping) override;

		float _getAngularDamping() const override;
		void _setAngularDamping(float angularDamping) override;

		float _getStaticFriction() const override;
		void _setStaticFriction(float friction) override;

		float _getDynamicFriction() const override;
		void _setDynamicFriction(float friction) override;

		float _getRestitution() const override;
		void _setRestitution(float restitution) override;

		Math::Vector3 _getLinearVelocity() const override;
		void _setLinearVelocity(const Math::Vector3 & linearVelocity) override;

		Math::Vector3 _getAngularVelocity() const override;
		void _setAngularVelocity(const Math::Vector3 & linearVelocity) override;

		Math::Vector3 _getMaxAngularVelocity() const override;
		void _setMaxAngularVelocity(const Math::Vector3 & linearVelocity) override;

		Math::Vector3 _getPosition() const override;
		void _setPosition(const Math::Vector3& position) override;

		Math::Quaternion _getRotation() const override;
		void _setRotation(const Math::Quaternion& rotation) override;

		PxUPtr<physx::PxRigidDynamic> _rigidbody;
		PxUPtr<physx::PxMaterial> _material;	
	public:
		DynamicCollider(IPhysicsEngine* physics);

		void ApplyForce(const Math::Vector3& force) override;
		void ApplyForce(const Math::Vector3& force, const Math::Vector3& center) override;
		void ApplyTorque(const Math::Vector3& force) override;

		void ApplyAcceleration(const Math::Vector3& acc) override;
		void ApplyAngularAcceleration(const Math::Vector3& acc) override;

		std::optional<float> Intersects(const Math::Ray& r) override;
		void UpdateTransform() override;
		void UpdateTransform(const Math::Vector3& position, const Math::Quaternion& rotation) override;

		void AttachShape(const Math::BoundingBox& box) override;
		void AttachShape(const Math::BoundingSphere& sphere) override;

		void SetKinematic(bool isKinematic) override;

		friend class PhysicsEngine;

		~DynamicCollider() override = default;
	};
}