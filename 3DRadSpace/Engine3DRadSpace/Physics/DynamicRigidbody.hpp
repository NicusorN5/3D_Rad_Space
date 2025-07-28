#pragma once
#include "IPhysicsObject.hpp"

namespace Engine3DRadSpace::Physics
{
	class E3DRSP_PHYSICS_EXPORT DynamicRigidbody : public IPhysicsObject
	{
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
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path & path) override;

		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo * GetGizmo() const noexcept override;

		void Draw3D() override;
		std::optional<float> Intersects(const Math::Ray & r) override;

		bool ApplyForce(const Math::Vector3 & force) override;
		bool ApplyForce(const Math::Vector3 & force, const Math::Vector3 & center) override;
		bool ApplyTorque(const Math::Vector3 & force) override;

		bool ApplyAcceleration(const Math::Vector3 & acc) override;
		bool ApplyAngularAcceleration(const Math::Vector3 & acc) override;

	};
}