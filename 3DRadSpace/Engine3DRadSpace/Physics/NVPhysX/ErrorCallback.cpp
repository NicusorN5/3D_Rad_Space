#include "ErrorCallback.hpp"
#include "../../Logging/Message.hpp"
#include "../../Logging/Warning.hpp"

using namespace Engine3DRadSpace::Physics::NVPhysX;
using namespace Engine3DRadSpace::Logging;

void ErrorCallback::reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line)
{
	std::string errorMessage = "PhysX Error: " + std::string(message) + " in file: " + std::string(file) + " at line: " + std::to_string(line);
	Logging::SetLastMessage(errorMessage);
}