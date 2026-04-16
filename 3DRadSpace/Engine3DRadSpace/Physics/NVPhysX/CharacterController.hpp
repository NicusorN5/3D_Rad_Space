#pragma once
#include "PhysicsEngine.hpp"
#include "../ICharacterController.hpp"
#include <characterkinematic/PxCapsuleController.h>

namespace Engine3DRadSpace::Physics::NVPhysX
{
	class E3DRSP_PHYSICS_OBJ_EXPORT CharacterController : public ICharacterController
	{
	protected:
		float _getMass() const override;
		void _setMass(float mass) override;

		void _setHeight(float height) override;
		float _getHeight() const override;

		void _setRadius(float radius) override;
		float _getRadius() const override;

		void _setMaxSlopeAngle(float angle) override;
		float _getMaxSlopeAngle() const override;

		Math::Vector3 _getGravity() const override;
		void _setGravity(const Math::Vector3& gravity) override;

		Math::Vector3 _getPosition() const override;
		void _setPosition(const Math::Vector3& position) override;

		Math::Quaternion _getRotation() const override;
		void _setRotation(const Math::Quaternion& rotation) override;

		PxUPtr<physx::PxMaterial> _material;
		PxUPtr<physx::PxCapsuleController> _controller;
		Math::Vector3 _verticalVelocity = Math::Vector3::Zero();

		Math::Vector3 _position;
	public:
		CharacterController(IPhysicsEngine* physics, float height, float radius);
		
		std::optional<float> Intersects(const Math::Ray& r) override;
		void UpdateTransform() override;
		void UpdateTransform(const Math::Vector3& position, const Math::Quaternion& rotation) override;
		
		void Move(const Math::Vector3& displacement) override;
		void Jump(float height) override;
		bool IsGrounded() override;

		~CharacterController() override = default;
	};
}