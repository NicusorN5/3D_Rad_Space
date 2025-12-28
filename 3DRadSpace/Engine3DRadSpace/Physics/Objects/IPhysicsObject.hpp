#pragma once
#include "../../Objects/IObject3D.hpp"
#include "../../Core/GetSet.hpp"
#include "../IPhysicsEngine.hpp"
#include "../ICollider.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// Base class for all objects that interact with the physics engine.
	/// </summary>
	class E3DRSP_PHYSICS_EXPORT IPhysicsObject : public Engine3DRadSpace::Objects::IObject3D
	{
	protected:
		IPhysicsEngine* _physics;

		IPhysicsObject();
		IPhysicsObject(IPhysicsEngine* physics);
	public:
		IPhysicsEngine* GetPhysics() const noexcept;
		virtual ICollider* GetBody() const noexcept = 0;

		virtual bool ApplyForce(const Math::Vector3& force) = 0;
		virtual bool ApplyForce(const Math::Vector3& force, const Math::Vector3& center) = 0;
		virtual bool ApplyTorque(const Math::Vector3& force) = 0;

		virtual bool ApplyAcceleration(const Math::Vector3& acc) = 0;
		virtual bool ApplyAngularAcceleration(const Math::Vector3& acc) = 0;

		void Initialize() override;

		virtual ~IPhysicsObject() = default;
	};
}