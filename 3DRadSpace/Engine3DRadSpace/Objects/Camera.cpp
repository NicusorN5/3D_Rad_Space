#include "Camera.hpp"
#include "../Reflection/Reflection.hpp"
#include "../Content/Assets/Model3D.hpp"
#include "../Game.hpp"
#include "../ObjectList.hpp"

#include "../Graphics/RenderTarget.hpp"

using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Math;

Camera::Camera(const std::string& name, bool visible, Vector3 pos, Vector3 look_at, Vector3 up,float aspectRatio, float fov, float npd, float fpd):
	IObject3D(name, visible, true, pos, Vector3::Zero(), Quaternion(), Vector3::One()),
	UpwardsDir(up),
	AspectRatio(aspectRatio),
	FieldOfView(fov),
	FarPlaneDistance(fpd),
	NearPlaneDistance(npd),
	LookAt(0,0,0),
	LookMode(CameraMode::UseRotation)
{
}

void Camera::EditorInitialize()
{
	Update();
}

static std::unique_ptr<Model3D> cameraModel;
static std::unique_ptr<RenderTarget> cameraPreview;
static std::unique_ptr<DepthStencilBuffer> cameraPreviewDepth;

static int cameraModelReferences = 0; //didn't use a shared_ptr to avoid using more fields inside the object.

void Camera::EditorLoad()
{
	if(cameraModel == nullptr)
	{
		cameraModel = std::make_unique<Model3D>(_game->Content->GetDevice(), "Data\\Models\\Camera.x");
	}
	if(cameraPreview == nullptr)
	{
		auto res = _game->Device->Resolution() / 4.0f;
		cameraPreview = std::make_unique<RenderTarget>(_game->Device.get(), res.X, res.Y);

		cameraPreviewDepth = std::make_unique<DepthStencilBuffer>(_game->Device.get(), res.X, res.Y);
	}

	++cameraModelReferences;
}

void Camera::EditorUpdate()
{
	Update();
}

Matrix4x4 Camera::GetViewMatrix() const noexcept
{
	Vector3 focus(0, 0, 0);
	switch (this->LookMode)
	{
	case CameraMode::UseRotation:
		focus = Position + Vector3::UnitZ().Transform(Rotation);
		break;
	case CameraMode::UseLookAtCoordinates:
		focus = this->LookAt;
		break;
	default: 
		std::unreachable();
	}

	return Matrix4x4::CreateLookAtView(Position, focus, UpwardsDir);
}

Matrix4x4 Camera::GetProjectionMatrix() const
{
	return Matrix4x4::CreatePerspectiveProjection(AspectRatio, FieldOfView, NearPlaneDistance, FarPlaneDistance);
}

void Camera::Draw3D()
{
	_game->View = GetViewMatrix();
	_game->Projection = GetProjectionMatrix();
	Update();
}

void Camera::Update() 
{ 
	_game->Objects->_camera = this;
}

Matrix4x4 Camera::GetModelMartix()
{
	return Matrix4x4::CreateFromQuaternion(Rotation) * Matrix4x4::CreateTranslation(Position);
}

void Camera::EditorDraw3D(bool selected)
{
	Update();
	cameraModel->Draw(GetModelMartix() * _game->View * _game->Projection);

	if(selected)
	{
		auto oldView = _game->View;
		auto oldProjection = _game->Projection;
		auto oldCamera = _game->Objects->_camera;

		_game->View = GetViewMatrix();
		_game->Projection = GetProjectionMatrix();
		_game->Objects->_camera = this;

		_game->Device->SetRenderTargetAndDepth(cameraPreview.get(), cameraPreviewDepth.get());
		//_game->Device->SetRenderTargetAndDisableDepth(cameraPreview.get());
		_game->Device->ClearRenderTarget(cameraPreview.get());
		_game->Device->ClearDepthBuffer(cameraPreviewDepth.get());
		_game->Device->SetViewport(
			Viewport{
				RectangleF(0,0, cameraPreview->Width(), cameraPreview->Height()),
				0.0f,
				1.0f
			}
		);

		for(auto& obj : (*_game->Objects))
		{
			if(obj.Object.get() == this) continue;

			if(obj.InternalType == ObjectList::ObjectInstance::ObjectType::IObject3D)
			{
				static_cast<IObject3D*>(obj.Object.get())->EditorDraw3D(false);
			}
		}

		_game->Device->SetViewport();
		_game->Device->SetRenderTargetAndDepth(nullptr, nullptr);

		_game->SpriteBatch->End();
		_game->SpriteBatch->Begin();
		_game->SpriteBatch->DrawNormalized(
			cameraPreview.get(),
			RectangleF(0.6f, 0.6f, 0.4f, 0.4f)
		);
		_game->SpriteBatch->End();

		_game->View = oldView;
		_game->Projection = oldProjection;
		_game->Objects->_camera = oldCamera;
	}
}

std::optional<float> Camera::Intersects(const Ray&r)
{
	auto f = r.Intersects(BoundingSphere(Position, 1.5f));
	if (f.has_value())
	{
		return f;
	}
	else return std::nullopt;
}

Engine3DRadSpace::Reflection::UUID Camera::GetUUID() const noexcept
{
	// {84376082-A56E-49E6-B095-BAEEF4BF29B5}
	return {0x84376082, 0xa56e, 0x49e6, { 0xb0, 0x95, 0xba, 0xee, 0xf4, 0xbf, 0x29, 0xb5 }};
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
	--cameraModelReferences;

	//Deallocate camera model early, to avoid DirectX debug layer STATE_CREATION warnings, despite the Camera editor model being a std::unique_ptr.
	if(cameraModelReferences == 0)
	{
		if(cameraModel != nullptr)
			cameraModel.reset();

		if(cameraPreview != nullptr)
			cameraPreview.reset();

		if(cameraPreviewDepth != nullptr)
			cameraPreview.reset();
	}

	//Remove the camera reference from the game object list.
	if(_game && _game->Objects->_camera == this)
	{
		_game->Objects->_camera = nullptr;
	}
}

REFL_BEGIN(Camera,"Camera","Camera objects","Perspective camera")
	REFL_FIELD(Camera, std::string, Name, "Name", "Camera", "Camera's name")
	REFL_FIELD(Camera, bool, Enabled, "Enabled", true, "Does the camera render the scene?")
	REFL_FIELD(Camera, Vector3, Position, "Position", Vector3::Zero(), "Camera position")
	REFL_FIELD(Camera, Quaternion, Rotation, "Rotation", Quaternion(), "Camera rotation")
	REFL_FIELD(Camera, Vector3, UpwardsDir, "Upwards direction", Vector3::One(), "Camera surface normal vector")
	REFL_FIELD(Camera, float, AspectRatio, "Aspect ratio", 4.f / 3.f, "Camera aspect ratio")
	REFL_FIELD(Camera, float, FieldOfView, "Field of view", 65.f, "Camera's field of view")
	REFL_FIELD(Camera, float, NearPlaneDistance, "Near plane distance", 0.01f, "Minimum drawing distance")
	REFL_FIELD(Camera, float, FarPlaneDistance, "Far plane distance", 500.f, "Maximum drawing distance")
REFL_END