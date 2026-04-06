#pragma once
#include "IPhysicsObject.hpp"
#include "IDynamicCollider.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// A physics object with a dynamic rigidbody collider.
	/// </summary>
	class E3DRSP_PHYSICS_EXPORT RigidDynamic : public IPhysicsObject
	{
	protected:
		std::unique_ptr<IDynamicCollider> _collider;

		struct physicsProperties
		{
			float mass = 0.0f;
			float linearDamping = 0.0f;
			float angularDamping = 0.0f;
			float staticFriction = 0.0f;
			float dynamicFriction = 0.0f;
			float restitution = 0.0f;
			Math::Vector3 linearVelocity = Math::Vector3::Zero();
			Math::Vector3 angularVelocity = Math::Vector3::Zero();
			Math::Vector3 maxAngularVelocity = Math::Vector3(100.0f, 100.0f, 100.0f);
		};

		std::unique_ptr<physicsProperties> _properties = std::make_unique<physicsProperties>();

		float _getMass() const noexcept;
		void _setMass(float mass);

		float _getLinearDamping() const noexcept;
		void _setLinearDamping(float linearDamping);

		float _getAngularDamping() const noexcept;
		void _setAngularDamping(float angularDamping);

		float _getStaticFriction() const noexcept;
		void _setStaticFriction(float friction);

		float _getDynamicFriction() const noexcept;
		void _setDynamicFriction(float friction);

		float _getRestitution() const noexcept;
		void _setRestitution(float restitution);

		Math::Vector3 _getLinearVelocity() const noexcept;
		void _setLinearVelocity(const Math::Vector3& linearVelocity);

		Math::Vector3 _getAngularVelocity() const noexcept;
		void _setAngularVelocity(const Math::Vector3& angularVelocity);

		Math::Vector3 _getMaxAngularVelocity() const noexcept;
		void _setMaxAngularVelocity(const Math::Vector3& maxAngularVelocity);

		bool _kinematic = false;
		bool _isKinematic() const noexcept;
		void _setKinematic(bool isKinematic);
	public:
		RigidDynamic(
			const std::string& name = "RigidDynamic",
			bool enabled = true,
			bool visible = true,
			const Math::Vector3& position = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3& scale = Math::Vector3::One()
		);
		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;
		void Draw3D() override;

		float Intersects(const Math::Ray& r) override;
		Reflection::UUID GetUUID() const noexcept override;
		Engine3DRadSpace::Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;

		void Teleport(const Math::Vector3& position, const std::optional<Math::Quaternion>& rotation = std::nullopt);

		GetSet<float, RigidDynamic, &_getMass, &_setMass> Mass;
		GetSet<float, RigidDynamic, &_getLinearDamping, &_setLinearDamping> LinearDamping;
		GetSet<float, RigidDynamic, &_getAngularDamping, &_setAngularDamping> AngularDamping;
		GetSet<float, RigidDynamic, &_getStaticFriction, &_setStaticFriction> StaticFriction;
		GetSet<float, RigidDynamic, &_getDynamicFriction, &_setDynamicFriction> DynamicFriction;
		GetSet<float, RigidDynamic, &_getRestitution, &_setRestitution> Restitution;
		GetSet<Math::Vector3, RigidDynamic, &_getLinearVelocity, &_setLinearVelocity> LinearVelocity;
		GetSet<Math::Vector3, RigidDynamic, &_getAngularVelocity, &_setAngularVelocity> AngularVelocity;
		GetSet<Math::Vector3, RigidDynamic, &_getMaxAngularVelocity, &_setMaxAngularVelocity> MaxAngularVelocity;
		GetSet<bool, RigidDynamic, &RigidDynamic::_isKinematic, &RigidDynamic::_setKinematic> Kinematic;

		IDynamicCollider* GetCollider() const noexcept;
	};
}

REFL_FWD(RigidDynamic)