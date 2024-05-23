#include "IPhysicsObject.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Reflection;

IPhysicsObject::IPhysicsObject(const std::string& name, bool enabled, bool visible, const Math::Vector3& pos, const Math::Vector3& pivot, 
							   const Math::Quaternion& rotation, const Math::Vector3& scale):
	IObject3D(name, enabled, visible, pos, pivot, rotation, scale)
{
}
