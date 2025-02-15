#include "MyGame.hpp"
#include <Windows.h>
#include <Engine3DRadSpace\Content\ShaderManager.hpp>

static int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
	MyGame game;
	game.Run();

	Engine3DRadSpace::Content::ShaderManager::ReleaseAll();
	return 0;
}