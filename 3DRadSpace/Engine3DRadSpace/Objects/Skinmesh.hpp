#pragma once

#include "../IObject3D.hpp"
#include "../Graphics/Model3D.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	using RefModel3D = Content::AssetID<Graphics::Model3D>;

	class DLLEXPORT Skinmesh : public IObject3D
	{
		Graphics::Model3D *_model;
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

		Graphics::Model3D *GetModel();

		void Initialize() override;
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void EditorInitialize() override;
		void EditorLoad() override;
		Reflection::UUID GetUUID() const noexcept override;
		void Draw3D() override;
		void EditorDraw3D(bool selected) override;
		std::optional<float> Intersects(const Math::Ray &r) override;

		~Skinmesh() override = default;
	};
}

REFL_FWD(Skinmesh)