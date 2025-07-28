#pragma once
#include "StaticRigidbody.hpp"
#include "DynamicRigidbody.hpp"

namespace Engine3DRadSpace::Physics
{
	class E3DRSP_PHYSICS_EXPORT Rigidbody : public IPhysicsObject
	{
		std::variant<StaticRigidbody, DynamicRigidbody, std::monostate> _rigidbody;
		bool _dynamic;
	public:
		Rigidbody();
		Rigidbody(StaticRigidbody&& staticRb);
		Rigidbody(DynamicRigidbody&& dynamicRb);

		void Initialize() override;
	};
}