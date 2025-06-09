#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Physics
{
	class PhysicsEngine;

	class E3DRSP_PHYSICS_EXPORT ICollider
	{
	protected:
		PhysicsEngine* _physics;

		ICollider(PhysicsEngine* physics);
	public:
		virtual ~ICollider() = default;
	};
}