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
) : IPhysicsObject(name, enabled, visible, position, rotation, scale),
	LinearDamping(this),
	StaticFriction(this),
	DynamicFriction(this),
	Restitution(this)
{
	_path = std::make_unique<std::string>(path.string());
}

RigidStatic::RigidStatic() : RigidStatic("RigidStatic", false, false, "")
{
	_path.reset();
}

float RigidStatic::_getLinearDamping() const noexcept
{
	if(_collider) return _collider->LinearDamping;
	return _properties->linearDamping;
}

void RigidStatic::_setLinearDamping(float linearDamping)
{
	if(_collider) _collider->LinearDamping = linearDamping;
	else _properties->linearDamping = linearDamping;
}

float RigidStatic::_getStaticFriction() const noexcept
{
	if(_collider) return _collider->StaticFriction;
	return _properties->staticFriction;
}

void RigidStatic::_setStaticFriction(float friction)
{
	if(_collider) _collider->StaticFriction = friction;
	else _properties->staticFriction = friction;
}

float RigidStatic::_getDynamicFriction() const noexcept
{
	if(_collider) return _collider->DynamicFriction;
	return _properties->dynamicFriction;
}

void RigidStatic::_setDynamicFriction(float friction)
{
	if(_collider) _collider->DynamicFriction = friction;
	else _properties->dynamicFriction = friction;
}

float RigidStatic::_getRestitution() const noexcept
{
	if(_collider) return _collider->Restitution;
	return _properties->restitution;
}

void RigidStatic::_setRestitution(float restitution)
{
	if(_collider) _collider->Restitution = restitution;
	else _properties->restitution = restitution;
}

void RigidStatic::Initialize()
{
	IPhysicsObject::Initialize();
}

void RigidStatic::Load()
{
	auto game = static_cast<Game*>(GetGame());

	if(_path)
	{
		_model = game->Content->Load<ModelAsset>(*_path)->Get();
		_collider = _physics->CreateStaticCollider(_model, Position, Rotation, Scale);

		_path.reset();
	}
	if(Model)
	{
		_model = const_cast<Model3D*>((*game->Content)[Model]->Get());
		_collider = _physics->CreateStaticCollider(_model, Position, Rotation, Scale);
	}

	if(_collider && _properties)
	{
		_collider->LinearDamping = _properties->linearDamping;
		_collider->StaticFriction = _properties->staticFriction;
		_collider->DynamicFriction = _properties->dynamicFriction;
		_collider->Restitution = _properties->restitution;
		_properties.reset();
	}
}

void RigidStatic::Load(const std::filesystem::path& path)
{
	auto game = static_cast<Game*>(GetGame());
	_model = game->Content->Load<ModelAsset>(*_path)->Get();
	_collider = _physics->CreateStaticCollider(_model, Scale);

	if(_collider && _properties)
	{
		_collider->LinearDamping = _properties->linearDamping;
		_collider->StaticFriction = _properties->staticFriction;
		_collider->DynamicFriction = _properties->dynamicFriction;
		_collider->Restitution = _properties->restitution;
		_properties.reset();
	}
}

void RigidStatic::Update()
{
	if(_collider != nullptr && _reqTransformUpdate)
	{
		_collider->UpdateTransform(Position, Rotation);
		_reqTransformUpdate = false;
	}
}

void RigidStatic::Draw3D()
{
	auto game = static_cast<Game*>(_game);

	if(Visible && _model)
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

Model3D* RigidStatic::GetModel() const noexcept
{
	return _model;
}

void RigidStatic::RequestTransformUpdate()
{
	_reqTransformUpdate = true;
}

template<>
class Engine3DRadSpace::Objects::Gizmos::Gizmo<RigidStatic> final : public Engine3DRadSpace::Objects::Gizmos::IGizmo
{
public:
	Gizmo()
	{
		Allow3DRendering = true;
		Allow2DRendering = false;
		AllowScaling = false;
		AllowRotating = true;
		AllowTranslating = true;
	}

	void Draw3D() override
	{
		if(!Object) return;
		if(!Object->Visible) return;

		auto rigidStatic = dynamic_cast<RigidStatic*>(Object);
		if(rigidStatic == nullptr) return;
		if(rigidStatic->GetModel() == nullptr) return;

		rigidStatic->Draw3D();
	}

	void Draw2D() override
	{
	}

	void Load() override
	{
		if(Object == nullptr) return;

		Object->Initialize();
		Object->Load();
	}

	void Load(const std::filesystem::path& path) override
	{
		if(Object == nullptr) return;

		Object->Initialize();
		Object->Load(path);
	}

	void Update() override
	{
		//Unlike Dynamic objects: update in case the user changed it in the editor
		auto rs = dynamic_cast<RigidStatic*>(Object);
		if(rs == nullptr) return;

		rs->RequestTransformUpdate();
		rs->Update();
	}

	~Gizmo() = default;
};

Gizmos::IGizmo* RigidStatic::GetGizmo() const noexcept
{
	return Internal::GizmoOf<RigidStatic>(this);
}

IStaticCollider* RigidStatic::GetCollider() const noexcept
{
	return _collider.get();
}

REFL_BEGIN(RigidStatic, "Rigidbody(Static)", "Physics", "Static rigidbody based off an mesh collider")
REFL_FIELD(RigidStatic, std::string, Name, "Name", "RigidStatic", "Name of the object")
REFL_FIELD(RigidStatic, bool, Enabled, "Enabled", true, "Whether the object is enabled or not")
REFL_FIELD(RigidStatic, bool, Visible, "Visible", true, "Whether the object is visible or not")
REFL_FIELD(RigidStatic, RefModel3D, Model, "Model", 0, "Model used for rendering and collision")
REFL_FIELD(RigidStatic, Vector3, Position, "Position", Vector3::Zero(), "Position of the object")
REFL_FIELD(RigidStatic, Quaternion, Rotation, "Rotation", Quaternion(), "Rotation of the object")
REFL_FIELD(RigidStatic, Vector3, Scale, "Scale", Vector3::One(), "Scale of the object (Only used at initialization!)")
REFL_FIELD(RigidStatic, float, LinearDamping, "Linear Damping", 0.0f, "Linear damping coefficient")
REFL_FIELD(RigidStatic, float, StaticFriction, "Static Friction", 0.5f, "Static friction of the material")
REFL_FIELD(RigidStatic, float, DynamicFriction, "Dynamic Friction", 0.5f, "Dynamic friction of the material")
REFL_FIELD(RigidStatic, float, Restitution, "Restitution", 0.5f, "Bounciness of the material")
REFL_END