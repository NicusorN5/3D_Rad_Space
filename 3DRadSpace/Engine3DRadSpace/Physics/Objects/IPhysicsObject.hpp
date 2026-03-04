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
		IPhysicsObject(IPhysicsEngine* physics);
	public:
		void Initialize() override;

		virtual ~IPhysicsObject() = default;
	};
}