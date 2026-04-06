#pragma once
#include "ICollider.hpp"

namespace Engine3DRadSpace::Physics
{
	class E3DRSP_PHYSICS_EXPORT ICharacterController : public ICollider
	{
	protected:
		ICharacterController(IPhysicsEngine *physics);

		float _height;

		virtual void _setHeight(float height) = 0;
		virtual float _getHeight() const noexcept = 0;

		float _radius;
		virtual void _setRadius(float radius) = 0;
		virtual float _getRadius() const noexcept = 0;

		float _maxSlopeAngle;
		virtual void _setMaxSlopeAngle(float angle) = 0;
		virtual float _getMaxSlopeAngle() const noexcept = 0;

		Math::Vector3 _gravity;
		virtual void _setGravity(const Math::Vector3& gravity) = 0;
		virtual Math::Vector3 _getGravity() const noexcept = 0;
	public:
		virtual void Move(const Math::Vector3& displacement) = 0;
		virtual void Jump(float height) = 0;

		GetSet<float, ICharacterController, &_getHeight, &_setHeight> Height;
		GetSet<float, ICharacterController, &_getRadius, &_setRadius> Radius;
		GetSet<float, ICharacterController, &_getMaxSlopeAngle, &_setMaxSlopeAngle> MaxSlopeAngle;
		GetSet<Math::Vector3, ICharacterController, &_getGravity, &_setGravity> Gravity;

		virtual bool IsGrounded() = 0;

		~ICharacterController() override = default;
	};
}