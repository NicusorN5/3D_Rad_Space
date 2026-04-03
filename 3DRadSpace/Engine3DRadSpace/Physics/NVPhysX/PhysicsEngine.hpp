#pragma once
#include "../PhysicsSettings.hpp"
#include "../IPhysicsEngine.hpp"

namespace physx
{
	class PxDefaultAllocator;
	class PxErrorCallback;
	class PxFoundation;
	class PxPvd;
	class PxPvdTransport;
	class PxPhysics;
	class PxDefaultCpuDispatcher;
	class PxScene;
}

namespace Engine3DRadSpace::Physics::NVPhysX
{
	/// <summary>
	/// Manages physics scene, and physics object factory.
	/// </summary>
	class E3DRSP_PHYSICS_NVPHYSX_EXPORT PhysicsEngine : public IPhysicsEngine
	{
		std::unique_ptr<physx::PxDefaultAllocator> _allocator;
		std::unique_ptr<physx::PxErrorCallback> _errCallback;

		physx::PxFoundation* _foundation = nullptr;
		physx::PxPvd* _pvd = nullptr;
		physx::PxPvdTransport* _pvdTransport = nullptr;

		physx::PxPhysics* _physics = nullptr;
		physx::PxDefaultCpuDispatcher* _cpuDispatcher = nullptr;
		physx::PxScene* _scene = nullptr;

		double _accTimer = 0;
		double _timeStep;
	public:
		PhysicsEngine(const PhysicsSettings& settings);

		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine(PhysicsEngine&&) = delete;

		PhysicsEngine& operator=(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(PhysicsEngine&&) = delete;

		void SetGravity(const Math::Vector3 &gravity);
		Math::Vector3 GetGravity();

		void Simulate(float dt) override;

		void* GetFoundation() const noexcept;
		void* GetPvd() const noexcept;
		void* GetPhysics() const noexcept;
		void* GetCPUDispatcher() const noexcept;
		void* GetScene() const noexcept override;

		std::unique_ptr<IStaticCollider> CreateStaticCollider(Graphics::Model3D* model, const Math::Vector3 &scale = Math::Vector3::One()) override;
		std::unique_ptr<IDynamicCollider> CreateDynamicCollider() override;

		~PhysicsEngine() override;
	};
}