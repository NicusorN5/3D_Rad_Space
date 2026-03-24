#include "SkinmeshPreviewer.hpp"
#include <Engine3DRadSpace/Objects/Impl/Skinmesh.hpp>
#include <Engine3DRadSpace/Objects/Impl/Camera.hpp>
#include "../Frontend/Settings.hpp"
#include <Engine3DRadSpace/Objects/ObjectList.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Math;

SkinmeshPreviewer::SkinmeshPreviewer(const std::filesystem::path &meshPath):
	Game(std::string("Skinmesh previewer -") + meshPath.string()),
	_camCoords(
		cosf(std::numbers::pi_v<float> / 6), //30 degrees = pi/6 radians
		sinf(std::numbers::pi_v<float> / 6)
	),
	_zoom(0),
	_initialZoom(0)
{
	auto [skinmesh, _] = this->Objects->AddNew<Skinmesh>("", true, meshPath);
	_skinmesh = skinmesh;

	auto [camera, _1] = this->Objects->AddNew<Camera>("", true);
	camera->SetLookAt(Vector3::Zero());
	_camera = camera;
}

void SkinmeshPreviewer::Load()
{
	_skinmesh->Load();
	_zoom = _initialZoom = _skinmesh->GetModel()->GetBoundingSphere().Radius * 2.0f;
}

void SkinmeshPreviewer::Update()
{
	static bool released = true;

	_zoom = _initialZoom - Mouse.ScrollWheel();
	if(Mouse.LeftButton() == ButtonState::Pressed && Window->IsFocused())
	{
		Point screenCenter = Window->Size() / 2;
		Point mousePos = Mouse.Position();
		Window->SetMousePosition(screenCenter);

		Point pd = screenCenter - mousePos;
		Vector2 mouseDelta = static_cast<Vector2>(pd) * float(Draw_dt);
		_camCoords -= mouseDelta * Settings::CameraSensitivity.Value;

		_camCoords.Y = std::clamp<float>(
			_camCoords.Y,
			-std::numbers::pi_v<float> / 2.0f + std::numeric_limits<float>::epsilon(),
			std::numbers::pi_v<float> / 2.0f - std::numeric_limits<float>::epsilon()
		);

		Window->MouseVisible = false;
		released = false;
	}
	else
	{
		if(!released)
		{
			released = true;
			Window->MouseVisible = true;
		}
	}

	_camera->Rotation = Quaternion::FromYawPitchRoll(_camCoords.X, _camCoords.Y, 0);
	_camera->Position = _zoom * Vector3::UnitZ().Transform(_camera->Rotation);
}