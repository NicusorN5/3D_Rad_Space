#pragma once
#include "../Core/IService.hpp"

namespace Engine3DRadSpace::Physics
{
	class E3DRSP_PHYSICS_EXPORT IPhysicsEngine : public IService
	{
	public:
		virtual void Simulate(float dt) = 0;
		virtual void* GetScene() const noexcept = 0;

		~IPhysicsEngine() override = default;
	};
}