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
		void _generateRigidbody();

		PxUPtr<physx::PxMaterial> _material;
		PxUPtr<physx::PxRigidStatic> _rigidbody;

		Graphics::Model3D* _model = nullptr;

		Math::Vector3 _position;
		Math::Quaternion _rotation;
		Math::Vector3 _scale;
	protected:
		float _getMass() override;
		void _setMass(float mass) override;

		float _getLinearDamping() override;
		void _setLinearDamping(float linearDamping) override;

		float _getStaticFriction() override;
		void _setStaticFriction(float friction) override;

		float _getDynamicFriction() override;
		void _setDynamicFriction(float friction) override;

		float _getRestitution() override;;
		void _setRestitution(float restitution) override;
	public:
		StaticMeshCollider(
			IPhysicsEngine* physics,
			Graphics::Model3D* model,
			const Math::Vector3 scale = Math::Vector3::One()
		);
	
		StaticMeshCollider(StaticMeshCollider&& rb) noexcept = default;
		StaticMeshCollider& operator=(StaticMeshCollider&& rb) noexcept = default;

		void SetPosition(const Math::Vector3& newPos, bool wake = false);
		void SetRotation(const Math::Quaternion& newQuat, bool wake = false);
		void SetPositionRotation(const Math::Vector3& newPos, const Math::Vector3& newQuat, bool wake);

		std::optional<float> Intersects(const Math::Ray& r) override;
		void UpdateTransform() override;

		friend class PhysicsEngine;

		~StaticMeshCollider() override = default;
	};
}