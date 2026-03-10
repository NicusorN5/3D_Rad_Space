#include "FreeCam.hpp"
#include "FreeCam.h"
#include "../../Math/Math.hpp"
#include "../../Games/Game.hpp"
#include "../Gizmos.hpp"
#include "../Gizmos/CameraGizmo.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

FreeCam::FreeCam() : Camera("FreeCam")
{
}

void FreeCam::Update()
{
	auto game = static_cast<Game*>(_game);
	float dt = game->Update_dt;

	auto screenCenter = game->Window->Size() / 2;
	Point mousePos = game->Mouse.Position();
	game->Window->SetMousePosition(screenCenter);

	auto mouseDelta = (Vector2)(screenCenter - mousePos);
	_camCoords -= mouseDelta * Sensitivity * dt;

	_camCoords.Y = std::clamp<float>(
		_camCoords.Y,
		-std::numbers::pi_v<float> / 2.f + 0.001f,
		std::numbers::pi_v<float> / 2.f - 0.001f
	);

	Rotation = Quaternion::FromYawPitchRoll(_camCoords.X, _camCoords.Y, 0);

	_fwd = Vector3::Transform(-Vector3::UnitZ(), Rotation);
	Vector3 right = Vector3::Normalize(Vector3::Cross(Normal, _fwd));

	auto &kb = game->Keyboard;

	Vector3 mv;

	if(kb.IsKeyDown(Forward)) mv += _fwd;
	if(kb.IsKeyDown(Backward)) mv -= _fwd;
	if(kb.IsKeyDown(Left)) mv -= right;
	if(kb.IsKeyDown(Right)) mv += right;

	if(kb.IsKeyDown(Elevate)) mv += Normal;
	if(kb.IsKeyDown(Descend)) mv -= Normal;

	if(mv.LengthSquared() > 0) mv.Normalize();

	Position += mv * MovementSpeed * dt;

	Camera::Update();
}

Reflection::UUID FreeCam::GetUUID() const noexcept
{
	// {FDA0C96A-3040-4E5C-B12C-D34577D99415}
	return {0xfda0c96a, 0x3040, 0x4e5c, { 0xb1, 0x2c, 0xd3, 0x45, 0x77, 0xd9, 0x94, 0x15 }};
}

Objects::Gizmos::IGizmo* FreeCam::GetGizmo() const noexcept
{
	return Internal::GizmoOf<Camera>(this);
}

Math::Vector3 FreeCam::ForwardDir() const noexcept
{
	return _fwd;
}

REFL_BEGIN(FreeCam, "FreeCam", "Camera objects", "Perspective camera")
	REFL_FIELD(FreeCam, std::string, Name, "Name", "FreeCam", "Camera's name")
	REFL_FIELD(FreeCam, bool, Enabled, "Enabled", true, "Does the camera render the scene?")
	REFL_FIELD(FreeCam, Vector3, Position, "Position", Vector3::Zero(), "Camera position")
	REFL_FIELD(FreeCam, Quaternion, Rotation, "Rotation", Quaternion(), "Camera rotation")
	REFL_FIELD(FreeCam, Vector3, Normal, "Normal", Vector3::UnitY(), "Camera surface normal vector")
	REFL_FIELD(FreeCam, float, AspectRatio, "Aspect ratio", 4.f / 3.f, "Camera aspect ratio")
	REFL_FIELD(FreeCam, float, FieldOfView, "Field of view", 65.f, "Camera's field of view")
	REFL_FIELD(FreeCam, float, NearPlaneDistance, "Near plane distance", 0.01f, "Minimum drawing distance")
	REFL_FIELD(FreeCam, float, FarPlaneDistance, "Far plane distance", 500.f, "Maximum drawing distance")
	REFL_FIELD(FreeCam, float, Sensitivity, "Sensitivity", 0.1f, "Mouse sensitivity")
	REFL_FIELD(FreeCam, float, MovementSpeed, "Movement speed", 1.0f, "Noclip camera movement speed")
	REFL_FIELD(FreeCam, bool, InvertX, "Invert X", false, "Invert X Axis")
	REFL_FIELD(FreeCam, bool, InvertY, "Invert Y", false, "Invert Y Axis")
	REFL_FIELD(FreeCam, Input::Key, Forward, "Forward", Input::Key::W, "Forward direction keybind")
	REFL_FIELD(FreeCam, Input::Key, Backward, "Backwards", Input::Key::S, "Backward direction keybind")
	REFL_FIELD(FreeCam, Input::Key, Left, "Left", Input::Key::A, "Left direction keybind")
	REFL_FIELD(FreeCam, Input::Key, Right, "Right", Input::Key::D, "Right direction keybind")
	REFL_METHOD(FreeCam, void, &Camera::Enable, "Enable")
	REFL_METHOD(FreeCam, Matrix4x4, &FreeCam::GetModelMatrix, "Get World Matrix")
	REFL_METHOD(FreeCam, Matrix4x4, &FreeCam::GetViewMatrix, "Get View Matrix")
	REFL_METHOD(FreeCam, Matrix4x4, &FreeCam::GetProjectionMatrix, "Get Projection Matrix")
REFL_END

E3DRSP_FreeCam E3DRSP_FreeCam_Create()
{
	return new FreeCam;
}

float E3DRSP_FreeCam_GetMovementSpeed(E3DRSP_FreeCam freecam)
{
	return static_cast<FreeCam*>(freecam)->MovementSpeed;
}

void E3DRSP_FreeCam_SetMovementSpeed(E3DRSP_FreeCam freecam, float speed)
{
	static_cast<FreeCam*>(freecam)->MovementSpeed = speed;
}

float E3DRSP_FreeCam_GetSensitivity(E3DRSP_FreeCam freecam)
{
	return static_cast<FreeCam*>(freecam)->Sensitivity;
}

void E3DRSP_FreeCam_SetSensitivity(E3DRSP_FreeCam freecam, float sensitivity)
{
	static_cast<FreeCam*>(freecam)->Sensitivity = sensitivity;
}

bool E3DRSP_FreeCam_IsXInverted(E3DRSP_FreeCam freecam)
{
	return static_cast<FreeCam*>(freecam)->InvertX;
}

void E3DRSP_FreeCam_SetXInverted(E3DRSP_FreeCam freecam, bool invertX)
{
	static_cast<FreeCam*>(freecam)->InvertX = invertX;
}

bool E3DRSP_FreeCam_IsYInverted(E3DRSP_FreeCam freecam)
{
	return static_cast<FreeCam*>(freecam)->InvertX;
}

void E3DRSP_FreeCam_SetYInverted(E3DRSP_FreeCam freecam, bool invertY)
{
	static_cast<FreeCam*>(freecam)->InvertY = invertY;
}

E3DRSP_Key E3DRSP_FreeCam_GetForwardKey(E3DRSP_FreeCam freecam)
{
	return static_cast<E3DRSP_Key>(static_cast<FreeCam*>(freecam)->Forward);
}

void E3DRSP_FreeCam_SetForwardKey(E3DRSP_FreeCam freecam, E3DRSP_Key key)
{
	static_cast<FreeCam*>(freecam)->Forward = static_cast<Input::Key>(key);
}

E3DRSP_Key E3DRSP_FreeCam_GetBackwardKey(E3DRSP_FreeCam freecam)
{
	return static_cast<E3DRSP_Key>(static_cast<FreeCam*>(freecam)->Backward);
}

void E3DRSP_FreeCam_SetBackwardKey(E3DRSP_FreeCam freecam, E3DRSP_Key key)
{
	static_cast<FreeCam*>(freecam)->Backward = static_cast<Input::Key>(key);
}

E3DRSP_Key E3DRSP_FreeCam_GetLeftKey(E3DRSP_FreeCam freecam)
{
	return static_cast<E3DRSP_Key>(static_cast<FreeCam*>(freecam)->Left);
}

void E3DRSP_FreeCam_SetLeftKey(E3DRSP_FreeCam freecam, E3DRSP_Key key)
{
	static_cast<FreeCam*>(freecam)->Left = static_cast<Input::Key>(key);
}

E3DRSP_Key E3DRSP_FreeCam_GetRightKey(E3DRSP_FreeCam freecam)
{
	return static_cast<E3DRSP_Key>(static_cast<FreeCam*>(freecam)->Right);
}
void E3DRSP_FreeCam_SetRightKey(E3DRSP_FreeCam freecam, E3DRSP_Key key)
{
	static_cast<FreeCam*>(freecam)->Right = static_cast<Input::Key>(key);
}