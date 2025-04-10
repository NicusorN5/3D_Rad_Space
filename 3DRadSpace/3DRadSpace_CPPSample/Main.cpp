#include "MyGame.hpp"
#include <Windows.h>
#include <Engine3DRadSpace\Content\ShaderManager.hpp>

int main()
{
	MyGame game;
	game.Run();

	Engine3DRadSpace::Content::ShaderManager::ReleaseAll();
	return 0;
}