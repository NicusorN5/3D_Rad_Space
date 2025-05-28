#pragma once

#include "../IObject3D.hpp"
#include "../Content/Assets/Model3D.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	using RefModel3D = Content::AssetID<Content::Assets::Model3D>;

	class DLLEXPORT Skinmesh : public IObject3D
	{
		Content::Assets::Model3D *_model;
		std::unique_ptr<std::string> _path;
	public:
		Skinmesh();

		Skinmesh(
			const std::string &name,
			bool visible, 
			RefModel3D model,
			const Math::Vector3 &pos,
			const Math::Quaternion &rot,
			const Math::Vector3 &pivot, 
			const Math::Vector3 &scale
		);

		Skinmesh(
			const std::string &name,
			bool visible, 
			const std::filesystem::path &path,
			const Math::Vector3 &pos = Math::Vector3::Zero(),
			const Math::Quaternion &rot = Math::Quaternion(),
			const Math::Vector3 &pivot = Math::Vector3::Zero(),
			const Math::Vector3 &scale = Math::Vector3::One()
		);

		RefModel3D Model;

		Content::Assets::Model3D *GetModel();

		void Initialize() override;
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		Reflection::UUID GetUUID() const noexcept override;
		void Draw3D() override;
		std::optional<float> Intersects(const Math::Ray &r) override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		~Skinmesh() override = default;
	};
}

REFL_FWD(Skinmesh)