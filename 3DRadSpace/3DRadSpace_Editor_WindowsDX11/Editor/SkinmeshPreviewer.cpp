#include "SkinmeshPreviewer.hpp"
#include <Engine3DRadSpace/Objects/Skinmesh.hpp>
#include <Engine3DRadSpace/Objects/Camera.hpp>
#include "../Frontend/Settings.hpp"
#include <Engine3DRadSpace/ObjectList.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Math;

SkinmeshPreviewer::SkinmeshPreviewer(const std::filesystem::path &meshPath):
	Game(std::string("Skinmesh previewer -") + meshPath.string()),
	_camCoords(
		cosf(std::numbers::pi_v<float> / 6), //30 degrees = pi/6 radians
		sinf(std::numbers::pi_v<float> / 6)
	)
{
	_basicShader.reset(new BasicTextured(Device.get()));

	_skinmesh = std::make_unique<Skinmesh>("", true, meshPath);
	_skinmesh->InternalInitialize(this);
	_skinmesh->Load();

	for (auto& meshPart : *_skinmesh->GetModel())
	{
		for (auto& modelMeshPart : *meshPart)
		{
			modelMeshPart->SetShaders(_basicShader);
		}
	}

	_zoom = _initialZoom = _skinmesh->GetModel()->GetBoundingSphere().Radius * 2.0f;

	_camera = std::make_unique<Camera>("");
	_camera->InternalInitialize(this);
	_camera->LookAt = Vector3::Zero();

	_camera->LookMode = Camera::CameraMode::UseLookAtCoordinates;

}

void SkinmeshPreviewer::Update()
{
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
	}
	Quaternion q = Quaternion::FromYawPitchRoll(-_camCoords.Y, 0, 0)* Quaternion::FromYawPitchRoll(0, -_camCoords.X, 0);
	_camera->Position = _zoom * Vector3::UnitZ().Transform(q);
}

void SkinmeshPreviewer::Draw3D()
{
	_camera->Draw3D();
	_skinmesh->Draw3D();
}
