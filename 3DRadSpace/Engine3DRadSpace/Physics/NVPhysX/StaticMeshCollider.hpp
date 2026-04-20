#pragma once
#include "../IStaticCollider.hpp"
#include "../Math/Quaternion.hpp"
#include <PxRigidStatic.h>
#include <PxPhysics.h>
#include "PxUptr.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Model3D;
}

namespace Engine3DRadSpace::Physics::NVPhysX
{
	/// <summary>
	/// Triangle mesh based static rigidbody collider.
	/// </summary>
	class E3DRSP_PHYSICS_OBJ_EXPORT StaticMeshCollider: public IStaticCollider
	{
	protected:
		void _generateRigidbody();

		PxUPtr<physx::PxMaterial> _material;
		PxUPtr<physx::PxRigidStatic> _rigidbody;

		Graphics::Model3D* _model = nullptr;

		Math::Vector3 _position = Math::Vector3::Zero();
		Math::Quaternion _rotation = Math::Quaternion();
		Math::Vector3 _scale = Math::Vector3::One();

		Math::Vector3 _oldPosition = Math::Vector3::Zero();
		Math::Quaternion _oldRotation = Math::Quaternion();

		float GetMass() const override;
		void SetMass(float mass) override;

		float GetLinearDamping() const override;
		void SetLinearDamping(float linearDamping) override;

		float GetStaticFriction() const override;
		void SetStaticFriction(float friction) override;

		float GetDynamicFriction() const override;
		void SetDynamicFriction(float friction) override;

		float GetRestitution() const override;
		void SetRestitution(float restitution) override;

		Math::Vector3 GetPosition() const noexcept override;
		void SetPosition(const Math::Vector3& position) override;

		Math::Quaternion GetRotation() const noexcept override;
		void SetRotation(const Math::Quaternion& rotation) override;
	public:
		StaticMeshCollider(
			IPhysicsEngine* physics,
			Graphics::Model3D* model,
			const Math::Vector3 &position = Math::Vector3::Zero(),
			const Math::Quaternion &rotation = Math::Quaternion(),
			const Math::Vector3 &scale = Math::Vector3::One()
		);
	
		StaticMeshCollider(StaticMeshCollider&& rb) noexcept = default;
		StaticMeshCollider& operator=(StaticMeshCollider&& rb) noexcept = default;

		std::optional<float> Intersects(const Math::Ray& r) override;
		void UpdateTransform() override;
		void UpdateTransform(const Math::Vector3& position, const Math::Quaternion& rotation) override;

		friend class PhysicsEngine;

		~StaticMeshCollider() override = default;
	};
}