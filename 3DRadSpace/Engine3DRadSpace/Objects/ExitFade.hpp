#pragma once
#include "IObject2D.hpp"
#include "..\Reflection\Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_EXPORT ExitFade : public IObject2D
	{
		float _timer = 0.0f;
	public:
		ExitFade(
			const std::string& name = "ExitFade",
			const std::filesystem::path& projectPath = "",
			Math::Color fadeColor = Math::Colors::Black, 
			float fadeTime = 5.0f
		);

		std::string ProjectPath;

		Math::Color FadeColor;
		float FadeTime;

		void Update() override;
		void Draw2D() override;

		// Inherited via IObject2D
		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		Reflection::UUID GetUUID() const noexcept override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}

REFL_FWD(ExitFade)