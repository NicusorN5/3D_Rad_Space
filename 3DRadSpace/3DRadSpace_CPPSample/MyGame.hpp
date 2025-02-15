#pragma once
#include <Engine3DRadSpace\Game.hpp>
#include <Engine3DRadSpace\Objects\Skinmesh.hpp>
#include <Engine3DRadSpace\Objects\Camera.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

class MyGame : public Game
{
	Skinmesh* _fish = nullptr;
	Camera* _cam = nullptr;
public:
	MyGame();

	void Initialize() override;
	void Load() override;
	void Update() override;
	void Draw3D() override;
	void Draw2D() override;

	~MyGame() = default;
};