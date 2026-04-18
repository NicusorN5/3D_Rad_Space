#pragma once
#include <Engine3DRadSpace\Games\Game.hpp>
#include <Engine3DRadSpace\Objects\Impl\Skinmesh.hpp>
#include <Engine3DRadSpace\Objects\Impl\TextPrint.hpp>
#include <Engine3DRadSpace\Physics\Objects\FPCharacter.hpp>
#include <Engine3DRadSpace\Audio\SoundInstance.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Physics::Objects;

class MyGame : public Game
{
	TextPrint* _text;
	FPCharacter* _character;
public:
	MyGame();

	//void Initialize() override;
	//void Load() override;
	void Update() override;
	//void Draw3D() override;
	//void Draw2D() override;

	~MyGame() = default;
};