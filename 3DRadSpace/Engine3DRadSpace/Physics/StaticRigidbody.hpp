#pragma once
#include "../Objects/Skinmesh.hpp"
#include "IPhysicsObject.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_PHYSICS_EXPORT StaticRigidbody: public Skinmesh, public Physics::IPhysicsObject
	{
		void _generateRigidbody();
	public:
		StaticRigidbody();
	
		void Load() override;
		void Load(const std::filesystem::path& path) override;

		Reflection::UUID GetUUID() const noexcept override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}