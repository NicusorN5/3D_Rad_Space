#include "StaticRigidbody.hpp"
#include "../Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Physics;

void StaticRigidbody::_generateRigidbody()
{
	//_game->Physics.get();
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
	// {2744F07F-05D5-4701-B7E6-1550DD763560}
	return { 0x2744f07f, 0x5d5, 0x4701, { 0xb7, 0xe6, 0x15, 0x50, 0xdd, 0x76, 0x35, 0x60 } };
}
