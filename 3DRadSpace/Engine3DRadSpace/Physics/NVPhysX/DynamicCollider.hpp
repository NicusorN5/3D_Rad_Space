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

		float _getMass() override;
		void _setMass(float mass) override;

		float _getLinearDamping() override;
		void _setLinearDamping(float linearDamping) override;

		float _getAngularDamping() override;
		void _setAngularDamping(float angularDamping) override;

		float _getStaticFriction() override;
		void _setStaticFriction(float friction) override;

		float _getDynamicFriction() override;
		void _setDynamicFriction(float friction) override;

		float _getRestitution() override;
		void _setRestitution(float restitution) override;

		Math::Vector3 _getLinearVelocity() override;
		void _setLinearVelocity(const Math::Vector3 & linearVelocity) override;

		Math::Vector3 _getAngularVelocity() override;
		void _setAngularVelocity(const Math::Vector3 & linearVelocity) override;

		Math::Vector3 _getMaxAngularVelocity() override;
		void _setMaxAngularVelocity(const Math::Vector3 & linearVelocity) override;

		PxUPtr<physx::PxRigidDynamic> _rigidbody;
		PxUPtr<physx::PxMaterial> _material;

		Math::Vector3 _position;
		Math::Quaternion _rotation;
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

		void Teleport(const Math::Vector3& position, const std::optional<Math::Quaternion>& rotation = std::nullopt) override;
		void SetKinematic(bool isKinematic) override;

		friend class PhysicsEngine;

		~DynamicCollider() override = default;
	};
}