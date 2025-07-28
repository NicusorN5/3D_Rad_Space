#include "PhysicsEngine.hpp"
#include <PxPhysicsAPI.h>
#include <extensions/PxDefaultAllocator.h>
#include "../Core/Logging/Exception.hpp"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Logging;

static void _pxDefaultAllocatorDeleter(void* _allocator)
{
	delete static_cast<physx::PxDefaultAllocator*>(_allocator);
}

static void _pxDefaultErrorCallbackDeleter(void* _errCallback)
{
	delete static_cast<physx::PxDefaultErrorCallback*>(_errCallback);
}

PhysicsEngine::PhysicsEngine(const PhysicsSettings& settings) :
	_timeStep(settings.TimeStep)
{
	if (!settings.PhysicsEnabled) return;

	_allocator = std::unique_ptr<void, std::function<void(void*)>> (new physx::PxDefaultAllocator, _pxDefaultAllocatorDeleter);
	_errCallback = std::unique_ptr<void, std::function<void(void*)>> (new physx::PxDefaultErrorCallback, _pxDefaultErrorCallbackDeleter);

	_foundation = PxCreateFoundation(
		PX_PHYSICS_VERSION,
		*static_cast<physx::PxDefaultAllocator*>(_allocator.get()),
		*static_cast<physx::PxDefaultErrorCallback*>(_errCallback.get())
	);
	if (_foundation == nullptr) throw Exception("Failed to create PxFoundation");
	auto foundation = static_cast<physx::PxFoundation*>(_foundation);

	_pvd = physx::PxCreatePvd(*foundation);
	auto pvd = (static_cast<physx::PxPvd*>(_pvd));

	_pvdTransport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	auto pvdTransport = static_cast<physx::PxPvdTransport*>(_pvdTransport);
	pvd->connect(*pvdTransport, physx::PxPvdInstrumentationFlag::eALL);

	bool trackMemoryAllocations = false;
#if _DEBUG
	trackMemoryAllocations = true;
#endif

	_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, physx::PxTolerancesScale(), trackMemoryAllocations, pvd);
	if (_physics == nullptr) throw Exception("Failed to create PxPhysics!");
	auto physics = static_cast<physx::PxPhysics*>(_physics);

	_cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(4);
	auto cpuDispatcher = static_cast<physx::PxDefaultCpuDispatcher*>(_cpuDispatcher);

	physx::PxSceneDesc sceneDesc(physics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(settings.Gravity.X, settings.Gravity.Y, settings.Gravity.Z);
	sceneDesc.cpuDispatcher = cpuDispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

	_scene = physics->createScene(sceneDesc);
	if (_scene == nullptr) throw Exception("Failed to create PxScene!");
}

void PhysicsEngine::SetGravity(const Math::Vector3& gravity)
{
	static_cast<physx::PxScene*>(_scene)->setGravity(physx::PxVec3(gravity.X, gravity.Y, gravity.Z));
}

Vector3 PhysicsEngine::GetGravity()
{
	auto g = static_cast<physx::PxScene*>(_scene)->getGravity();
	return Vector3(g.x, g.y, g.z);
}

void PhysicsEngine::Simulate(float dt)
{
	for (_accTimer += dt; _accTimer >= _timeStep; _accTimer -= _timeStep)
	{
		auto scene = static_cast<physx::PxScene*>(_scene);
		scene->simulate(dt);
		scene->fetchResults(false);
	}
}

void* PhysicsEngine::GetFoundation() const noexcept
{
	return _foundation;
}

void* PhysicsEngine::GetPvd() const noexcept
{
	return _pvd;
}

void* PhysicsEngine::GetPhysics() const noexcept
{
	return _physics;
}

void* PhysicsEngine::GetCPUDispatcher() const noexcept
{
	return  _cpuDispatcher;
}

void* PhysicsEngine::GetScene() const noexcept
{
	return _scene;
}

PhysicsEngine::~PhysicsEngine()
{
	auto scene = static_cast<physx::PxScene*>(_scene);
	auto cpuDispatcher = static_cast<physx::PxDefaultCpuDispatcher*>(_cpuDispatcher);
	auto physics = static_cast<physx::PxPhysics*>(_physics);
	auto pvd = (static_cast<physx::PxPvd*>(_pvd));

	//PX_RELEASE(scene);
	if(scene)
	{
		scene->release(); 
		_scene = nullptr;
	}

	//PX_RELEASE(cpuDispatcher);
	if(cpuDispatcher) 
	{
		cpuDispatcher->release();
		_cpuDispatcher = nullptr;
	}
	//PX_RELEASE(physics);
	if(physics) 
	{
		physics->release();
		_physics = nullptr;
	}

	if (pvd)
	{
		physx::PxPvdTransport* transport = pvd->getTransport();
		PX_RELEASE(transport);

		pvd->release();
		_pvd = nullptr;
	}

	auto foundation = static_cast<physx::PxFoundation*>(_foundation);
	//PX_RELEASE(foundation);
	if(foundation)
	{
		foundation->release();
		_foundation = nullptr;
	};
}
