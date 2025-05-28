#pragma once
#include "../IObject2D.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class DLLEXPORT SkyColor : public IObject
	{
	public:
		SkyColor(const std::string& name ="SkyColor", bool enabled = true, Color color = Colors::Black);

		Color Colour;

		void Initialize() override;
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		Reflection::UUID GetUUID() const noexcept override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;

	};
}

REFL_FWD(SkyColor)