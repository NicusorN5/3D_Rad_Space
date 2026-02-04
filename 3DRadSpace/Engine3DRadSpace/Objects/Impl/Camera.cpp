#include "Camera.hpp"
#include "../Reflection/Reflection.hpp"
#include "../Games/Game.hpp"
#include "ObjectList.hpp"
#include "Gizmos/CameraGizmo.hpp"
#include "Gizmos.hpp"

#include "../Graphics/IRenderTarget.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Math;

Camera::Camera(
	const std::string& name,
	bool visible,
	const Vector3 &pos, 
	const Vector3 &look_at, 
	const Vector3 &up,
	float aspectRatio,
	float fov, 
	float npd, 
	float fpd
):
	IObject3D(name, visible, true, pos, Vector3::Zero(), Quaternion::FromVectorToVector(look_at, up), Vector3::One()),
	Normal(up),
	AspectRatio(aspectRatio),
	FieldOfView(fov),
	FarPlaneDistance(fpd),
	NearPlaneDistance(npd),
	LookAt( pos + Vector3::Transform(Vector3::Forward(), Quaternion::FromVectorToVector(look_at, up))),
	LookMode(CameraMode::UseRotation)
{
}

Matrix4x4 Camera::GetViewMatrix() const noexcept
{
	Vector3 focus(0, 0, 0);
	switch (this->LookMode)
	{
	case CameraMode::UseRotation:
		focus = Position + Vector3::Forward().Transform(Rotation);
		break;
	case CameraMode::UseLookAtCoordinates:
		focus = this->LookAt;
		break;
	default:
		std::unreachable();
	}

	return Matrix4x4::CreateLookAtView(Position, focus, Normal);
}

Matrix4x4 Camera::GetProjectionMatrix() const
{
	return Matrix4x4::CreatePerspectiveProjection(AspectRatio, FieldOfView, NearPlaneDistance, FarPlaneDistance);
}

void Camera::Draw3D()
{
	if(Visible)
	{
		auto game = static_cast<Game*>(_game);

		game->View = GetViewMatrix();
		game->Projection = GetProjectionMatrix();
		Update();
	}
}

void Camera::Update() 
{ 
	if(Visible)
	{
		auto game = static_cast<Game*>(_game);
		game->Objects->_camera = this;
	}
}

void Camera::ForceUpdate()
{
	auto game = static_cast<Game*>(_game);

	game->Objects->_camera = this;
	game->View = GetViewMatrix();
	game->Projection = GetProjectionMatrix();
}

Matrix4x4 Camera::GetModelMatrix()
{
	return Matrix4x4::CreateFromQuaternion(Rotation) * Matrix4x4::CreateTranslation(Position);
}

float Camera::Intersects(const Ray&r)
{
	return r.Intersects(BoundingSphere(Position, 1.5f));
}

Engine3DRadSpace::Reflection::UUID Camera::GetUUID() const noexcept
{
	// {84376082-A56E-49E6-B095-BAEEF4BF29B5}
	return {0x84376082, 0xa56e, 0x49e6, { 0xb0, 0x95, 0xba, 0xee, 0xf4, 0xbf, 0x29, 0xb5 }};
}

Gizmos::IGizmo* Camera::GetGizmo() const noexcept
{
	return Internal::GizmoOf<Camera>(this);
}

void Camera::Initialize()
{
	Update();
}

void Camera::Load()
{
}

void Camera::Load(const std::filesystem::path& path)
{
}

Camera::~Camera()
{
	//Remove the camera reference from the game object list.
	if(_game)
	{
		if(auto game = static_cast<Game*>(_game); game->Objects->_camera == this)
		game->Objects->_camera = nullptr;
	}
}

REFL_BEGIN(Camera,"Camera","Camera objects","Perspective camera")
	REFL_FIELD(Camera, std::string, Name, "Name", "Camera", "Camera's name")
	REFL_FIELD(Camera, bool, Enabled, "Enabled", true, "Does the camera render the scene?")
	REFL_FIELD(Camera, Vector3, Position, "Position", Vector3::Zero(), "Camera position")
	REFL_FIELD(Camera, Quaternion, Rotation, "Rotation", Quaternion(), "Camera rotation")
	REFL_FIELD(Camera, Vector3, Normal, "Normal", Vector3::UnitY(), "Camera surface normal vector")
	REFL_FIELD(Camera, float, AspectRatio, "Aspect ratio", 4.f / 3.f, "Camera aspect ratio")
	REFL_FIELD(Camera, float, FieldOfView, "Field of view", 65.f, "Camera's field of view")
	REFL_FIELD(Camera, float, NearPlaneDistance, "Near plane distance", 0.01f, "Minimum drawing distance")
	REFL_FIELD(Camera, float, FarPlaneDistance, "Far plane distance", 500.f, "Maximum drawing distance")
	REFL_METHOD(Camera, void, &Camera::Enable, "Enable")
	REFL_METHOD(Camera, Matrix4x4, &Camera::GetModelMatrix, "Get World Matrix")
	REFL_METHOD(Camera, Matrix4x4, &Camera::GetViewMatrix, "Get View Matrix")
	REFL_METHOD(Camera, Matrix4x4, &Camera::GetProjectionMatrix, "Get Projection Matrix")
REFL_END