//#include "MyGame.hpp"
#include "Engine3DRadSpace/Games/Game.hpp"
#include <Windows.h>

class MyGame : public Engine3DRadSpace::Game
{
public:
	MyGame() : Game("MyGame", 800, 600)
	{
		AppendScene("C:\\Users\\ms_ep\\Desktop\\rsgrgsg.3drsp");
	}
	~MyGame() override = default;
};

int WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	MyGame game;
	game.Run();

	return 0;
}