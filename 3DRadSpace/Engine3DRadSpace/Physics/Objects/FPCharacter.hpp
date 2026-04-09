#pragma once
#include "IPhysicsObject.hpp"
#include "../../Objects/Impl/FreeCam.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	class E3DRSP_PHYSICS_OBJ_EXPORT FPCharacter : public IPhysicsObject
	{
	public:
		FPCharacter();



		~FPCharacter() override = default;
	};
}