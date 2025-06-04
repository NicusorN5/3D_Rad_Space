#pragma once
#include <Engine3DRadSpace\Games\Game.hpp>
#include <Engine3DRadSpace\Objects\Skinmesh.hpp>
#include <Engine3DRadSpace\Objects\Camera.hpp>
#include <Engine3DRadSpace\Audio\SoundInstance.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Graphics;

class MyGame : public Game
{
	Skinmesh* _fish = nullptr;
	Camera* _cam = nullptr;

	Sound* _sound = nullptr;
	std::unique_ptr<SoundInstance> _soundInstance;
public:
	MyGame();

	void Initialize() override;
	void Load() override;
	void Update() override;
	void Draw3D() override;
	void Draw2D() override;

	~MyGame() = default;
};