#pragma once
#include "IPhysicsObject.hpp"
#include "../IStaticCollider.hpp"
#include "../../Objects/Impl/Skinmesh.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// Represents an static rigidboby made from an mesh collider.
	/// </summary>
	class E3DRSP_PHYSICS_OBJ_EXPORT RigidStatic : public IPhysicsObject
	{
		std::unique_ptr<IStaticCollider> _collider = nullptr;
		std::unique_ptr<std::string> _path;

		Graphics::Model3D* _model = nullptr;
	public:
		RigidStatic();
		RigidStatic(
			const std::string& name,
			bool enabled,
			bool visible,
			const std::filesystem::path& path,
			const Math::Vector3 position = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3& scale = Math::Vector3::One()
		);

		Engine3DRadSpace::Objects::RefModel3D Model;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;
		void Draw3D() override;

		float Intersects(const Math::Ray& r) override;
		Engine3DRadSpace::Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
		Reflection::UUID GetUUID() const noexcept override;

		~RigidStatic() override = default;
	};
}

REFL_FWD(RigidStatic)