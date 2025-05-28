#pragma once
#include "../IObject3D.hpp"
#include "../Content/Assets/SkyboxAsset.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects 
{
	using RefSkybox = Content::AssetID<Content::Assets::SkyboxAsset>;
	class DLLEXPORT Skybox : public IObject3D
	{
		Content::Assets::SkyboxAsset *_skybox;
		std::unique_ptr<std::string> _path;
	public:
		Skybox(const std::string& name = "Skybox", bool visible = false, RefSkybox skybox = 0);
		Skybox(const std::string& name, bool visible, const std::filesystem::path& path);

		RefSkybox SkyboxID;

		void Initialize() override;
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		Reflection::UUID GetUUID() const noexcept override;
		void Draw3D() override;

		std::optional<float> Intersects(const Math::Ray& r) override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		~Skybox() override = default;
	};
}

REFL_FWD(Skybox)