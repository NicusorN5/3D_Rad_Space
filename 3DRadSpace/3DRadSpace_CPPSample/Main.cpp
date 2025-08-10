#include "MyGame.hpp"
#include <Windows.h>
#include <Engine3DRadSpace\Graphics\Shaders\ShaderManager.hpp>

int WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	MyGame game;
	game.Run();

	Engine3DRadSpace::Graphics::Shaders::ShaderManager::ReleaseAll();
	return 0;
}