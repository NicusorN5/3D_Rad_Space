#pragma once
#include "PhysicsSettings.hpp"
#include "IPhysicsEngine.hpp"

namespace Engine3DRadSpace::Physics
{
	/// <summary>
	/// Manages physics scene, and physics object factory.
	/// </summary>
	class E3DRSP_PHYSICS_EXPORT PhysicsEngine : public IPhysicsEngine
	{
		std::unique_ptr<void, std::function<void(void*)>> _allocator;
		std::unique_ptr<void, std::function<void(void*)>> _errCallback;

		//physx::PxFoundation*
		void* _foundation;
		//physx::PxPvd
		void* _pvd;
		//physx::PxPvdTransport
		void* _pvdTransport;

		///physx::PxPhysics
		void* _physics;
		//physx::PxDefaultCpuDispatcher
		void* _cpuDispatcher;

		//physx::PxScene
		void* _scene;

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

		~PhysicsEngine() override;
	};
}