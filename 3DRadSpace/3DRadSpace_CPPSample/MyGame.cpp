#include "MyGame.hpp"
#include <Engine3DRadSpace\Objects\Skinmesh.hpp>
#include <Engine3DRadSpace\Objects\Camera.hpp>
#include <Engine3DRadSpace\ObjectList.hpp>
#include <Engine3DRadSpace\Math\Quaternion.hpp>
#include <Engine3DRadSpace\Graphics\Primitives\Plane.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;

MyGame::MyGame() : Game("3DRadSpace Empty", 800, 600)
{
}

void MyGame::Initialize()
{
	Game::Initialize();

	this->ClearColor = Colors::CornflowerBlue;

	//Add a camera viewing the fish model
	Camera cam;
	cam.Position = { 0, 1, 1.5 };
	cam.Rotation = Quaternion::FromYawPitchRoll(0, 0, 0);
	cam.LookAt = { 0,0,0 };
	cam.LookMode = Camera::CameraMode::UseLookAtCoordinates;
	_cam = this->Objects->AddNew(std::move(cam)).first; //first is object pointer, second is ID.

	//Directly create a fish model into the scene
	_fish = this->Objects->AddNew<Skinmesh>("fish", true, "Data\\Models\\YellowFish.x").first;
}

void MyGame::Load()
{
	Game::Load();

	//_sound = this->Content->Load<Sound>("Data\\Sounds\\sound.wav");
	//_soundInstance = std::make_unique<SoundInstance>(_sound);
	//_soundInstance->SetLooping(true);

	// zoom the camera into the model.
	float distance = _fish->GetModel()->GetBoundingSphere().Radius + 0.25f;
	_cam->Position *= distance;

	_plane = std::make_unique<Graphics::Primitives::Plane>(Device.get(), Colors::Red, Vector2::One());
}

void MyGame::Update()
{
	Game::Update();
	//rotate the model around the Y axis.
	_fish->Rotation *= Quaternion::FromYawPitchRoll(0, this->Draw_dt, 0);
	_fish->Rotation.Normalize();

	if(Keyboard.IsKeyDown(Key::Space))
	{
		//_soundInstance->Play();
	}
}

void MyGame::Draw3D()
{
	Game::Draw3D();

	_plane->View = View;
	_plane->Projection = Projection;

	_plane->Draw3D();
}

void MyGame::Draw2D()
{
	Game::Draw2D();
}
