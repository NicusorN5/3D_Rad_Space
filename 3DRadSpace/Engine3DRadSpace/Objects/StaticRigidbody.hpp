#pragma once
#include "Skinmesh.hpp"
#include "../Physics/IPhysicsObject.hpp"

namespace Engine3DRadSpace::Objects
{
	class StaticRigidbody: public Skinmesh, public Physics::IPhysicsObject
	{
		void _generateRigidbody();
	public:
		StaticRigidbody();
	
		void Load() override;
		void Load(const std::filesystem::path& path) override;

		Reflection::UUID GetUUID() const noexcept override;
	};
}