#include "RigidStatic.hpp"
#include "../../Games/Game.hpp"
#include "../../Content/Assets/ModelAsset.hpp"
#include "../../Objects/Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::Objects;

RigidStatic::RigidStatic(
	const std::string& name,
	bool enabled,
	bool visible, 
	const std::filesystem::path& path,
	const Vector3 position,
	const Quaternion& rotation,
	const Vector3& scale
) : IPhysicsObject(name, enabled, visible, position, rotation, scale)
{
	_path = std::make_unique<std::string>(path.string());
}

RigidStatic::RigidStatic() : RigidStatic("RigidStatic", false, false, "")
{
	_path.reset();
}

void RigidStatic::Initialize()
{
	IPhysicsObject::Initialize();
}

void RigidStatic::Load()
{
	if(_path)
	{
		auto game = static_cast<Game*>(GetGame());
		_model = game->Content->Load<ModelAsset>(*_path)->Get();
		_collider = _physics->CreateStaticCollider(_model, Scale);

		_path.reset();
	}
}

void RigidStatic::Load(const std::filesystem::path& path)
{
	auto game = static_cast<Game*>(GetGame());
	_model = game->Content->Load<ModelAsset>(*_path)->Get();
	_collider = _physics->CreateStaticCollider(_model, Scale);
}

void RigidStatic::Update()
{
	if(_collider != nullptr)
		_collider->UpdateTransform();
}

void RigidStatic::Draw3D()
{
	auto game = static_cast<Game*>(_game);

	if(Visible && _model && _collider)
		_model->Draw(GetModelMatrix() * game->View * game->Projection);
}

float RigidStatic::Intersects(const Math::Ray& r)
{
	if(_collider == nullptr) return std::numeric_limits<float>::signaling_NaN();
	return _collider->Intersects(r).value_or(std::numeric_limits<float>::signaling_NaN());
}

Reflection::UUID RigidStatic::GetUUID() const noexcept
{
	// {11E67CA3-19A3-4558-8528-72A03F0901F9}
	return {0x11e67ca3, 0x19a3, 0x4558, { 0x85, 0x28, 0x72, 0xa0, 0x3f, 0x9, 0x1, 0xf9 }};
}

Gizmos::IGizmo* RigidStatic::GetGizmo() const noexcept
{
	return nullptr;
}

REFL_BEGIN(RigidStatic, "Rigidbody(Static)", "Physics", "Static rigidbody based off an mesh collider")
REFL_FIELD(RigidStatic, std::string, Name, "Name", "RigidStatic", "Name of the object")
REFL_FIELD(RigidStatic, bool, Enabled, "Enabled", true, "Whether the object is enabled or not")
REFL_FIELD(RigidStatic, bool, Visible, "Visible", true, "Whether the object is visible or not")
REFL_FIELD(RigidStatic, RefModel3D, Model, "Model", 0, "Model used for rendering and collision")
REFL_FIELD(RigidStatic, Vector3, Position, "Position", Vector3::Zero(), "Position of the object")
REFL_FIELD(RigidStatic, Quaternion, Rotation, "Rotation", Quaternion(), "Rotation of the object")
REFL_FIELD(RigidStatic, Vector3, Scale, "Scale", Vector3::One(), "Scale of the object (Only used at initialization!)")
REFL_END