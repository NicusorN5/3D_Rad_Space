#pragma once
#include "../Math/Vector3.hpp"
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
		virtual float _getMass() = 0;
		virtual void _setMass(float mass) = 0;

		ICollider(IPhysicsEngine* physics);
	public:
		GetSet<float, ICollider, &_getMass, &_setMass> Mass;

		IPhysicsEngine* GetPhysics() const noexcept;

		virtual std::optional<float> Intersects(const Math::Ray& r) = 0;
		virtual void UpdateTransform() = 0;
		virtual void UpdateTransform(const Math::Vector3& position, const Math::Quaternion& rotation) = 0;

		virtual ~ICollider() = default;
	};
}