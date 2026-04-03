#pragma once
#include "../../Core/Libs.hpp"
#include <PxPhysicsAPI.h>

namespace Engine3DRadSpace::Physics::NVPhysX
{
	class E3DRSP_PHYSICS_NVPHYSX_EXPORT ErrorCallback : public physx::PxErrorCallback
	{
	public:
		ErrorCallback() = default;

		virtual void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override;
		~ErrorCallback() = default;
	};
}