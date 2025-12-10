#include "IGame.hpp"

using namespace Engine3DRadSpace;

IService* IGame::GetService(const std::type_index &type)
{
	return _services[type];
}

IService* IGame::RequireService(const std::type_index& type)
{
	if (auto s1 = GetService(type); s1 != nullptr) return s1;

	return nullptr;
}

std::unordered_map<std::type_index, IService*>::iterator IGame::begin()
{
	return _services.begin();
}

std::unordered_map<std::type_index, IService*>::iterator IGame::end()
{
	return _services.end();
}