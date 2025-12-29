#include "IGame.hpp"
#include "IGame.h"

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

void E3DRSP_IGame_Exit(E3DRSP_IGame game)
{
	assert(game != nullptr);
	static_cast<IGame*>(game)->Exit();
}

bool E3DRSP_IGame_WasInitialized(E3DRSP_IGame game)
{
	if (game == nullptr) return false;
	return static_cast<IGame*>(game)->WasInitialized();
}

bool E3DRSP_IGame_WasLoaded(E3DRSP_IGame game)
{
	if (game == nullptr) return false;
	return static_cast<IGame*>(game)->WasLoaded();
}

void E3DRSP_IGame_AppendScene(E3DRSP_IGame game, const char* path)
{
	if (game == nullptr || path == nullptr) return;
	static_cast<IGame*>(game)->AppendScene(std::filesystem::path(path));
}

void E3DRSP_IGame_Destroy(E3DRSP_IGame game)
{
	assert(game != nullptr);
	delete static_cast<IGame*>(game);
}