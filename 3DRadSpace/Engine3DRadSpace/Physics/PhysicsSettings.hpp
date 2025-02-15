/// ------------------------------------------------------------------------------------------------
/// File:   Physics/PhysicsSettings.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "../Math/Vector3.hpp"

namespace Engine3DRadSpace::Physics
{
	struct PhysicsSettings
	{
		bool PhysicsEnabled;
		Math::Vector3 Gravity;
		double TimeStep;
	};
}