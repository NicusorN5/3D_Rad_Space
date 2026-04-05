#include "RigidDynamic.hpp"
#include "../../Objects/Impl/Box.hpp"
#include "../../Objects/Impl/Sphere.hpp"
#include "../../Objects/Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::Objects;
using namespace Engine3DRadSpace::Objects;

RigidDynamic::RigidDynamic(
	const std::string& name,
	bool enabled,
	bool visible,
	const Math::Vector3& position,
	const Math::Quaternion& rotation,
	const Math::Vector3& scale
) : IPhysicsObject(name, enabled, visible, position, rotation, scale),
	Mass(this),
	LinearDamping(this),
	AngularDamping(this),
	StaticFriction(this),
	DynamicFriction(this),
	Restitution(this),
	LinearVelocity(this),
	AngularVelocity(this),
	MaxAngularVelocity(this)
{
}

float RigidDynamic::_getMass() const noexcept
{
	if(_collider) return _collider->Mass;
	return _properties->mass;
}

void RigidDynamic::_setMass(float mass)
{
	if(_collider) _collider->Mass = mass;
	else _properties->mass = mass;
}

float RigidDynamic::_getLinearDamping() const noexcept
{
	if(_collider) return _collider->LinearDamping;
	return _properties->linearDamping;
}

void RigidDynamic::_setLinearDamping(float linearDamping)
{
	if(_collider) _collider->LinearDamping = linearDamping;
	else _properties->linearDamping = linearDamping;
}

float RigidDynamic::_getAngularDamping() const noexcept
{
	if(_collider) return _collider->AngularDamping;
	return _properties->angularDamping;
}

void RigidDynamic::_setAngularDamping(float angularDamping)
{
	if(_collider) _collider->AngularDamping = angularDamping;
	else _properties->angularDamping = angularDamping;
}

float RigidDynamic::_getStaticFriction() const noexcept
{
	if(_collider) return _collider->StaticFriction;
	return _properties->staticFriction;
}

void RigidDynamic::_setStaticFriction(float friction)
{
	if(_collider) _collider->StaticFriction = friction;
	else _properties->staticFriction = friction;
}

float RigidDynamic::_getDynamicFriction() const noexcept
{
	if(_collider) return _collider->DynamicFriction;
	return _properties->dynamicFriction;
}

void RigidDynamic::_setDynamicFriction(float friction)
{
	if(_collider) _collider->DynamicFriction = friction;
	else _properties->dynamicFriction = friction;
}

float RigidDynamic::_getRestitution() const noexcept
{
	if(_collider) return _collider->Restitution;
	return _properties->restitution;
}

void RigidDynamic::_setRestitution(float restitution)
{
	if(_collider) _collider->Restitution = restitution;
	else _properties->restitution = restitution;
}

Math::Vector3 RigidDynamic::_getLinearVelocity() const noexcept
{
	if(_collider) return _collider->LinearVelocity;
	return _properties->linearVelocity;
}

void RigidDynamic::_setLinearVelocity(const Math::Vector3& linearVelocity)
{
	if(_collider) _collider->LinearVelocity = linearVelocity;
	else _properties->linearVelocity = linearVelocity;
}

Math::Vector3 RigidDynamic::_getAngularVelocity() const noexcept
{
	if(_collider) return _collider->AngularVelocity;
	return _properties->angularVelocity;
}

void RigidDynamic::_setAngularVelocity(const Math::Vector3& angularVelocity)
{
	if(_collider) _collider->AngularVelocity = angularVelocity;
	else _properties->angularVelocity = angularVelocity;
}

Math::Vector3 RigidDynamic::_getMaxAngularVelocity() const noexcept
{
	if(_collider) return _collider->MaxAngularVelocity;
	return _properties->maxAngularVelocity;
}

void RigidDynamic::_setMaxAngularVelocity(const Math::Vector3& maxAngularVelocity)
{
	if(_collider) _collider->MaxAngularVelocity = maxAngularVelocity;
	else _properties->maxAngularVelocity = maxAngularVelocity;
}

void RigidDynamic::Initialize()
{
	IPhysicsObject::Initialize();
	_collider = _physics->CreateDynamicCollider();

	for(auto& child : Children)
	{
		if(child == nullptr) continue;

		bool isShape = false;

		if(dynamic_cast<Engine3DRadSpace::Objects::Box*>(child) != nullptr)
		{
			isShape = true;

			auto box = dynamic_cast<Engine3DRadSpace::Objects::Box*>(child);
			Math::BoundingBox bbox(box->Position, box->Scale);

			_collider->AttachShape(bbox);
		}

		if(dynamic_cast<Engine3DRadSpace::Objects::Sphere*>(child) != nullptr)
		{
			isShape = true;
			auto sphere = dynamic_cast<Engine3DRadSpace::Objects::Sphere*>(child);
			Math::BoundingSphere sph(sphere->Position, sphere->Radius);

			_collider->AttachShape(sph);
		}

		if(isShape)
		{
			child->Visible = false;
			child->Enabled = false;
		}
	}

	if(_properties)
	{
		_collider->Mass = _properties->mass;
		_collider->LinearDamping = _properties->linearDamping;
		_collider->AngularDamping = _properties->angularDamping;
		_collider->StaticFriction = _properties->staticFriction;
		_collider->DynamicFriction = _properties->dynamicFriction;
		_collider->Restitution = _properties->restitution;
		_collider->LinearVelocity = _properties->linearVelocity;
		_collider->AngularVelocity = _properties->angularVelocity;
		_collider->MaxAngularVelocity = _properties->maxAngularVelocity;
	}
	_properties.reset();

	_collider->UpdateTransform(Position, Rotation);
}

void RigidDynamic::Load()
{
}

void RigidDynamic::Load(const std::filesystem::path& path)
{
}

void RigidDynamic::Update()
{
	if(_collider)
		_collider->UpdateTransform();
}

void RigidDynamic::Teleport(const Math::Vector3& position, const std::optional<Math::Quaternion>& rotation)
{
	_collider->UpdateTransform(position, Rotation);
}

float RigidDynamic::Intersects(const Math::Ray& r)
{
	constexpr float nan = std::numeric_limits<float>::signaling_NaN();

	if(_collider == nullptr) return nan;
	return _collider->Intersects(r).value_or(nan);
}

Reflection::UUID RigidDynamic::GetUUID() const noexcept
{
	// {E360B70E-266C-4B9B-A14C-62979B930D3C}
	return {0xe360b70e, 0x266c, 0x4b9b, { 0xa1, 0x4c, 0x62, 0x97, 0x9b, 0x93, 0xd, 0x3c }};
}

template<>
class Engine3DRadSpace::Objects::Gizmos::Gizmo<RigidDynamic> final : public Engine3DRadSpace::Objects::Gizmos::IGizmo
{
	bool _wasLoaded = false;
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
	}

	void Draw2D() override
	{
	}

	void Load() override
	{
	}

	void Load(const std::filesystem::path& path) override
	{
	}

	void Update() override
	{
	}

	~Gizmo() = default;
};

Gizmos::IGizmo* RigidDynamic::GetGizmo() const noexcept
{
	return Internal::GizmoOf<RigidDynamic>(this);
}

REFL_BEGIN(RigidDynamic, "RigidDynamic", "Physics", "A physics object with dynamic rigidbody colliders")
REFL_FIELD(RigidDynamic, std::string, Name, "Name", "RigidDynamic", "Object of the name")
REFL_FIELD(RigidDynamic, bool, Enabled, "Enabled", true, "Is the physics object active?")
REFL_FIELD(RigidDynamic, Math::Vector3, Position, "Position", Math::Vector3::Zero(), "World position of the physics object")
REFL_FIELD(RigidDynamic, Math::Quaternion, Rotation, "Rotation", Math::Quaternion(), "World rotation of the physics object")
REFL_FIELD(RigidDynamic, float, Mass, "Mass", 1.0f, "Mass of the rigidbody")
REFL_FIELD(RigidDynamic, float, LinearDamping, "Linear Damping", 0.0f, "Linear damping coefficient")
REFL_FIELD(RigidDynamic, float, AngularDamping, "Angular Damping", 0.05f, "Angular damping coefficient")
REFL_FIELD(RigidDynamic, float, StaticFriction, "Static Friction", 0.5f, "Static friction of the material")
REFL_FIELD(RigidDynamic, float, DynamicFriction, "Dynamic Friction", 0.5f, "Dynamic friction of the material")
REFL_FIELD(RigidDynamic, float, Restitution, "Restitution", 0.5f, "Bounciness of the material")
REFL_END