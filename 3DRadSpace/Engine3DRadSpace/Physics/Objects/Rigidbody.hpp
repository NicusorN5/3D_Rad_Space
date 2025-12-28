#pragma once
#include "IPhysicsObject.hpp"
#include "../ICollider.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	class E3DRSP_PHYSICS_OBJ_EXPORT Rigidbody : public IPhysicsObject
	{
		std::unique_ptr<ICollider> _rigidbody;
		bool _dynamic;
	public:
		Rigidbody();
		//Rigidbody(StaticRigidbody&& staticRb);
		//Rigidbody(DynamicRigidbody&& dynamicRb);

		void Initialize() override;
	};
}