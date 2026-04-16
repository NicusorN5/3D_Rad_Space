#pragma once
#include "../Math/Vector3.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/Ray.hpp"
#include "../Core/GetSet.hpp"
#include "../Core/IUpdateable.hpp"

namespace Engine3DRadSpace::Physics
{
	class IPhysicsEngine;

	class E3DRSP_PHYSICS_EXPORT ICollider
	{
	protected:
		IPhysicsEngine* _physics;

		float _mass;
		virtual float _getMass() const = 0;
		virtual void _setMass(float mass) = 0;

		Math::Vector3 _position;
		virtual Math::Vector3 _getPosition() const = 0;
		virtual void _setPosition(const Math::Vector3& position) = 0;

		Math::Quaternion _rotation;
		virtual Math::Quaternion _getRotation() const = 0;
		virtual void _setRotation(const Math::Quaternion& rotation) = 0;

		ICollider(IPhysicsEngine* physics);
	public:
		GetSet<float, ICollider, &_getMass, &_setMass> Mass;
		GetSet<Math::Vector3, ICollider, &_getPosition, &_setPosition> Position;
		GetSet<Math::Quaternion, ICollider, &_getRotation, &_setRotation> Rotation;

		IPhysicsEngine* GetPhysics() const noexcept;

		virtual std::optional<float> Intersects(const Math::Ray& r) = 0;
		virtual void UpdateTransform() = 0;
		virtual void UpdateTransform(const Math::Vector3& position, const Math::Quaternion& rotation) = 0;

		virtual ~ICollider() = default;
	};
}