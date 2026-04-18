#include "MyGame.hpp"
#include <Engine3DRadSpace/Objects/ObjectList.hpp>

MyGame::MyGame() : Game("FPCharacter Demo", 1280, 720)
{
	AppendScene(R"(D:\Projects\3D_Rad_Space\3DRadSpace\out\build\x64-Release\Projects\FPCharacter Demo.3drsp)");

	_text = Objects->Find<TextPrint>();
	_character = Objects->Find<FPCharacter>();
}

void MyGame::Update()
{
	_text->Text = std::format("Position {} {} {}", _character->Position.X, _character->Position.Y, _character->Position.Z );

	Game::Update();
}