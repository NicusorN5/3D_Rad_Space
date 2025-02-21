#pragma once
#include "..\IObject2D.hpp"
#include "..\Reflection\Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class DLLEXPORT ExitFade : public IObject2D
	{
		float _timer = 0.0f;
	public:
		ExitFade(
			const std::string& name = "ExitFade",
			const std::filesystem::path& projectPath = "",
			Color fadeColor = Colors::Black, 
			float fadeTime = 5.0f
		);

		std::string ProjectPath;

		Color FadeColor;
		float FadeTime;

		void Update() override;
		void Draw2D() override;

		// Inherited via IObject2D
		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void EditorInitialize() override;
		void EditorLoad() override;
		void EditorUpdate() override;
		Reflection::UUID GetUUID() const noexcept override;
		void EditorDraw2D(bool selected) override;
	};
}

REFL_FWD(ExitFade)