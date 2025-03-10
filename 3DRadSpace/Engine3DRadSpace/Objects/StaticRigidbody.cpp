#include "StaticRigidbody.hpp"
#include "../Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Physics;

void StaticRigidbody::_generateRigidbody()
{
	_game->Physics.get();
}

StaticRigidbody::StaticRigidbody() :
	Skinmesh()
{
}

void StaticRigidbody::Load()
{
	Skinmesh::Load();
}

void StaticRigidbody::Load(const std::filesystem::path &path)
{
	Skinmesh::Load(path);
}

Reflection::UUID StaticRigidbody::GetUUID() const noexcept
{

}
