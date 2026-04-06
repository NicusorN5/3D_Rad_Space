#pragma once
#include "PhysicsEngine.hpp"
#include "../ICharacterController.hpp"
#include <characterkinematic/PxCapsuleController.h>

namespace Engine3DRadSpace::Physics::NVPhysX
{
	class E3DRSP_PHYSICS_OBJ_EXPORT CharacterController : public ICharacterController
	{
	protected:
		void _setHeight(float height) override;
		float _getHeight() const noexcept override;
		void _setRadius(float radius) override;
		float _getRadius() const noexcept override;
		void _setMaxSlopeAngle(float angle) override;
		float _getMaxSlopeAngle() const noexcept override;
		Math::Vector3 _getGravity() const noexcept override;
		void _setGravity(const Math::Vector3& gravity) override;

		PxUPtr<physx::PxCapsuleController> _controller;
		Math::Vector3 _verticalVelocity = Math::Vector3::Zero();
	public:
		CharacterController(IPhysicsEngine* physics, float height, float radius);
		void Move(const Math::Vector3& displacement) override;
		void Jump(float height) override;
		bool IsGrounded() override;

		~CharacterController() override = default;
	};
}