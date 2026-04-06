#include "CharacterController.hpp"
#include <characterkinematic/PxControllerManager.h>
#include <characterkinematic/PxController.h>
#include <characterkinematic/PxCapsuleController.h>
#include <PxPhysics.h>
#include <PxScene.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::NVPhysX;

CharacterController::CharacterController(
	IPhysicsEngine* physics,
	float height, 
	float radius
) : ICharacterController(physics)
{
	_height = height;
	_radius = radius;

	auto nvPhysics = static_cast<physx::PxPhysics*>(static_cast<PhysicsEngine*>(physics)->GetPhysics());
	auto nvControllerManager = static_cast<physx::PxControllerManager*>(static_cast<PhysicsEngine*>(physics)->_controllerManager.get());

	physx::PxCapsuleControllerDesc desc;
	desc.setToDefault();
	desc.height = height;
	desc.radius = radius;
	desc.slopeLimit = 0.707f; // 45 deg

	auto controller = nvControllerManager->createController(desc);
	_controller.reset(static_cast<physx::PxCapsuleController*>(controller));

	auto scene = static_cast<physx::PxScene*>(physics->GetScene());
	auto g = scene->getGravity();
	_gravity = Vector3(g.x, g.y, g.z);
}

void CharacterController::_setHeight(float height)
{
	_height = height;
	if(_controller)
		_controller->resize(height);
}

float CharacterController::_getHeight() const noexcept
{
	if(_controller)
		return _controller->getHeight();
	return _height;
}

void CharacterController::_setRadius(float radius)
{
	_radius = radius;
	if(_controller)
		_controller->setRadius(radius);
}

float CharacterController::_getRadius() const noexcept
{
	if(_controller)
		return _controller->getRadius();
	return _radius;
}

float CharacterController::_getMaxSlopeAngle() const noexcept
{
	if(_controller)
		return std::acos(_controller->getSlopeLimit());
	return _maxSlopeAngle;
}

void CharacterController::_setMaxSlopeAngle(float angle)
{
	_maxSlopeAngle = angle;
	if(_controller)
		_controller->setSlopeLimit(std::cos(angle));
}

Math::Vector3 CharacterController::_getGravity() const noexcept
{
	return _gravity;
}

void CharacterController::_setGravity(const Math::Vector3& gravity)
{
	_gravity = gravity;
}

void CharacterController::Move(const Math::Vector3& displacement)
{
	if(!_controller) return;

	float dt = static_cast<float>(_physics->dt());

	_verticalVelocity += Gravity.Get() * dt;

	if(IsGrounded() && _verticalVelocity.Y <= 0.0f)
		_verticalVelocity = Vector3::Zero();

	physx::PxVec3 motion =
		physx::PxVec3(displacement.X, displacement.Y, displacement.Z) + (physx::PxVec3(_verticalVelocity.X, _verticalVelocity.Y, _verticalVelocity.Z) * dt);

		_controller->move(
			motion,
			0.001f,
			_physics->dt(),
			physx::PxControllerFilters(),
			nullptr
		);
}

void CharacterController::Jump(float height)
{
	if(!IsGrounded()) return;

	float g = _gravity.Length();
	_verticalVelocity = Vector3(0, std::sqrt(2.0f * g * height), 0);
}

bool CharacterController::IsGrounded()
{
	if(_controller)
	{
		physx::PxControllerState state;
		_controller->getState(state);

		return (state.collisionFlags & physx::PxControllerCollisionFlag::eCOLLISION_DOWN) != 0;
	}

	return false;
}

float CharacterController::_getMass()
{
	return 0.0f;
}

void CharacterController::_setMass(float mass)
{
	// Do nothing, character controller doesn't have mass
}

std::optional<float> CharacterController::Intersects(const Math::Ray& r)
{
	return std::nullopt;
}

void CharacterController::UpdateTransform()
{
	if(!_controller) return;

	auto p = _controller->getPosition();
	_position = Vector3(static_cast<float>(p.x), static_cast<float>(p.y), static_cast<float>(p.z));
}

void CharacterController::UpdateTransform(const Math::Vector3& position, const Math::Quaternion& rotation)
{
	if(!_controller) return;
	_controller->setPosition(physx::PxExtendedVec3(position.X, position.Y, position.Z));
}