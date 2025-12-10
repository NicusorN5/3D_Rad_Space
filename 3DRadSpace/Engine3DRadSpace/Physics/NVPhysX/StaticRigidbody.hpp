#pragma once
#include "../ICollider.hpp"
#include "../Math/Quaternion.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Model3D;
}

namespace Engine3DRadSpace::Physics::NVPhysX
{
	/// <summary>
	/// Triangle mesh based static rigidbody collider.
	/// </summary>
	class E3DRSP_PHYSICS_OBJ_EXPORT StaticRigidbody: public ICollider
	{
		void _generateRigidbody();

		STD_UPtrTypeless _material;
		STD_UPtrTypeless _rigidbody;

		Graphics::Model3D* _model = nullptr;

		Math::Vector3 _position;
		Math::Quaternion _rotation;
		Math::Vector3 _scale;
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

		float _getRestitution() override;;
		void _setRestitution(float restitution) override;

		Math::Vector3 _getLinearVelocity() override;
		void _setLinearVelocity(const Math::Vector3& linearVelocity) override;

		Math::Vector3 _getAngularVelocity() override;
		void _setAngularVelocity(const Math::Vector3& linearVelocity) override;

		Math::Vector3 _getMaxAngularVelocity() override;
		void _setMaxAngularVelocity(const Math::Vector3& linearVelocity) override;
	public:
		StaticRigidbody(
			IPhysicsEngine* physics,
			Graphics::Model3D* model,
			const Math::Vector3 scale = Math::Vector3::One()
		);
	
		StaticRigidbody(StaticRigidbody&& rb) noexcept = default;
		StaticRigidbody& operator=(StaticRigidbody&& rb) noexcept = default;

		bool ApplyForce(const Math::Vector3& force) override;
		bool ApplyForce(const Math::Vector3& force, const Math::Vector3& center) override;
		bool ApplyTorque(const Math::Vector3& force) override;

		bool ApplyAcceleration(const Math::Vector3& acc) override;
		bool ApplyAngularAcceleration(const Math::Vector3& acc) override;

		void SetPosition(const Math::Vector3& newPos, bool wake = false);
		void SetRotation(const Math::Quaternion& newQuat, bool wake = false);
		void SetPositionRotation(const Math::Vector3& newPos, const Math::Vector3& newQuat, bool wake);

		std::optional<float> Intersects(const Math::Ray& r) override;
		void Update() override;

		~StaticRigidbody() override = default;
	};
}