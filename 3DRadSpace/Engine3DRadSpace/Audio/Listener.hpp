#pragma once
#include "../Math/Vector3.hpp"

namespace Engine3DRadSpace::Audio
{
	struct Listener
	{
		float Volume = 1.0f;
		Math::Vector3 Position = Math::Vector3::Zero();
		Math::Vector3 Velocity = Math::Vector3::Zero();

		Math::Vector3 Direction = Math::Vector3::UnitZ();
		Math::Vector3 Normal = Math::Vector3::UnitY();
	
		bool Enabled = true;
	};
}