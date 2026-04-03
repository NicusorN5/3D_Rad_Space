#pragma once
#include "../Core/IService.hpp"
#include "../Math/Vector3.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Model3D;
}

namespace Engine3DRadSpace::Physics
{
	class IStaticCollider;
	class IDynamicCollider;

	class E3DRSP_PHYSICS_EXPORT IPhysicsEngine : public IService
	{
	public:
		virtual void Simulate(float dt) = 0;
		virtual void* GetScene() const noexcept = 0;

		virtual std::unique_ptr<IStaticCollider> CreateStaticCollider(Graphics::Model3D* model, const Math::Vector3 &scale = Math::Vector3::One()) = 0;
		virtual std::unique_ptr<IDynamicCollider> CreateDynamicCollider() = 0;

		~IPhysicsEngine() override = default;
	};
}