#pragma once

namespace Engine3DRadSpace::Physics
{
	class PhysicsEngine;

	class ICollider
	{
	protected:
		PhysicsEngine* _physics;

		ICollider(PhysicsEngine* physics);
	public:
		virtual ~ICollider() = default;
	};
}