#include "MyGame.hpp"
#include <Windows.h>
#include <Engine3DRadSpace\Content\ShaderManager.hpp>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdArgs, int nShowCmd)
{
	MyGame game;
	game.Run();

	Engine3DRadSpace::Content::ShaderManager::ReleaseAll();
	return 0;
}