/// ------------------------------------------------------------------------------------------------
/// File:   Physics/PhysicsEngine.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "PhysicsSettings.hpp"

//PhysX class forward declarations - TODO : REMOVE.
namespace physx
{
	class PxDefaultAllocator;
	class PxDefaultErrorCallback;
}

namespace Engine3DRadSpace::Physics
{
	/// <summary>
	/// Manages physics scene, and physics object factory.
	/// </summary>
	class DLLEXPORT PhysicsEngine
	{
		std::unique_ptr<physx::PxDefaultAllocator> _allocator;
		std::unique_ptr<physx::PxDefaultErrorCallback> _errCallback;

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

		void Simulate(float dt);

		~PhysicsEngine();
	};
}