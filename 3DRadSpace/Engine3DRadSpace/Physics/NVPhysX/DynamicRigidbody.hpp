#pragma once
#include "../ICollider.hpp"

namespace Engine3DRadSpace::Physics::NVPhysX
{
	class E3DRSP_PHYSICS_OBJ_EXPORT DynamicRigidbody : public ICollider
	{
	protected:
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
	public:
		DynamicRigidbody(IPhysicsEngine* physics);

		bool ApplyForce(const Math::Vector3& force) override;
		bool ApplyForce(const Math::Vector3& force, const Math::Vector3& center) override;
		bool ApplyTorque(const Math::Vector3& force) override;

		bool ApplyAcceleration(const Math::Vector3& acc) override;
		bool ApplyAngularAcceleration(const Math::Vector3& acc) override;

		std::optional<float> Intersects(const Math::Ray& r) override;
		void Update() override;

		~DynamicRigidbody() override = default;
	};
}