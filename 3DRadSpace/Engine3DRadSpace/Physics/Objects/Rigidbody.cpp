#include "Rigidbody.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::Objects;

Rigidbody::Rigidbody() :
	_dynamic(false)
{

}

//Rigidbody::Rigidbody(StaticRigidbody&& staticRb) :
//	_rigidbody(std::move(staticRb)),
//	_dynamic(false)
//{
//}
//
//Rigidbody::Rigidbody(DynamicRigidbody&& dynamicRb) :
//	_rigidbody(std::move(dynamicRb)),
//	_dynamic(true)
//{
//
//}

void Rigidbody::Initialize()
{
	IPhysicsObject::Initialize();
}
