#include "IGame.hpp"

using namespace Engine3DRadSpace;

IService* IGame::GetService(const std::type_index &type)
{
	return _services[type];
}

std::unordered_map<std::type_index, IService*>::iterator IGame::begin()
{
	return _services.begin();
}

std::unordered_map<std::type_index, IService*>::iterator IGame::end()
{
	return _services.end();
}