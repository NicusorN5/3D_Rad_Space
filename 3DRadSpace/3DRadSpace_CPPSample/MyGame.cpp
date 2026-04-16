#include "MyGame.hpp"

MyGame::MyGame() : Game("FPCharacter Demo", 1280, 720)
{
	AppendScene(R"(D:\Projects\3D_Rad_Space\3DRadSpace\out\build\x64-Release\Projects\FPCharacter Demo.3drsp)");
}