#include "MyGame.hpp"
#include <Engine3DRadSpace\Objects\Skinmesh.hpp>
#include <Engine3DRadSpace\Objects\Camera.hpp>
#include <Engine3DRadSpace\ObjectList.hpp>
#include <Engine3DRadSpace\Math\Quaternion.hpp>

using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Math;

MyGame::MyGame() : Game("3DRadSpace Empty", 800, 600)
{
}

void MyGame::Initialize()
{
	Game::Initialize();

	this->RequestAudioInitialization();
	this->RequestPhysicsInitialization({0, -9.8f, 0});
	this->ClearColor = Colors::CornflowerBlue;

	//Add a camera viewing the fish model
	Camera cam;
	cam.Position = { 0, 1, 1.5 };
	cam.Rotation = Quaternion::FromYawPitchRoll(Math::ToRadians(90.f), 0, 0);
	cam.LookAt = { 0,0,0 };
	cam.LookMode = Camera::CameraMode::UseLookAtCoordinates;
	_cam = this->Objects->AddNew(std::move(cam)).first; //first is object pointer, second is ID.

	//Directly create a fish model into the scene
	_fish = this->Objects->AddNew<Skinmesh>("fish", true, "Data\\Models\\YellowFish.x").first;
}

void MyGame::Load()
{
	Game::Load();

	// zoom the camera into the model.
	float distance = _fish->GetModel()->GetBoundingSphere().Radius + 0.25f;
	_cam->Position *= distance;
}

void MyGame::Update()
{
	Game::Update();
	//rotate the model around the Y axis.
	_fish->Rotation *= Quaternion::FromYawPitchRoll(this->Draw_dt, 0, 0);
	_fish->Rotation.Normalize();
}

void MyGame::Draw3D()
{
	Game::Draw3D();
}

void MyGame::Draw2D()
{
	Game::Draw2D();
}
