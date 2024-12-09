#pragma once
#include "../IObject2D.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class SkyColor : public IObject2D
	{
	public:
		SkyColor(const std::string& name ="SkyColor", bool enabled = true, Color color = Colors::Black);

		Color Colour;

		// Inherited via IObject2D
		void Initialize() override;
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void EditorInitialize() override;
		void EditorLoad() override;
		Reflection::UUID GetUUID() const noexcept override;

		// Inherited via IObject2D
		void Draw2D() override;
		void EditorDraw2D(bool selected) override;
	};
}

REFL_FWD(SkyColor)