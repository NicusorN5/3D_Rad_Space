#pragma once
#include "../IScript.hpp"
#include "../../Objects/IObject.hpp"
#include "../../Reflection/Reflection.hpp"
#include <nethost.h>

namespace Engine3DRadSpace::Scripting::CSharp
{
	/// <summary>
	/// A script object handing a AngelScript source.
	/// </summary>
	class __declspec(dllexport) CSharpScript final : public Engine3DRadSpace::Objects::IObject
	{
		
	public:
		CSharpScript(
			const std::string& name = "C# Script",
			bool enabled = true,
			const std::string& src = ""
		);

		std::string ScriptPath;
		std::string Class;

		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;

		~CSharpScript() override = default;
	};
}

REFL_FWD(CSharpScript)