/// ------------------------------------------------------------------------------------------------
/// File:   Physics/StaticRigidbody.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "PhysicsEngine.hpp"
#include "IPhysicsObject.hpp"

namespace Engine3DRadSpace::Physics
{
	class StaticRigidbody : public IPhysicsObject
	{
	public:
		StaticRigidbody(
			const std::string& name = "StaticRigidbody",
			bool enabled = true,
			Math::Vector3 pos = Math::Vector3::One(),
			Math::Quaternion rotation = Math::Quaternion(),
			Math::Vector3 scale = Math::Vector3::One()
		);
	};
}