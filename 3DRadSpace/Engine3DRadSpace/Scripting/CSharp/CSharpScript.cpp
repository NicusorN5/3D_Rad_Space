#include "CSharpScript.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Scripting;
using namespace Engine3DRadSpace::Scripting::CSharp;

CSharpScript::CSharpScript(
	const std::string& name,
	bool enabled,
	const std::string& src
)
{
}

Reflection::UUID CSharpScript::GetUUID() const noexcept
{
	// {8B607307-5FF3-4019-9416-493EA100E0B2}
	return { 0x8b607307, 0x5ff3, 0x4019, { 0x94, 0x16, 0x49, 0x3e, 0xa1, 0x0, 0xe0, 0xb2 } };
}

Objects::Gizmos::IGizmo* CSharpScript::GetGizmo() const noexcept
{
	return nullptr;
}

void CSharpScript::Initialize()
{

}

void CSharpScript::Load()
{
}

void CSharpScript::Load(const std::filesystem::path& path)
{
}

void CSharpScript::Update()
{
}

REFL_BEGIN(CSharpScript, "C# Script", "Scripting", "AngelScript script")
REFL_FIELD(CSharpScript, std::string, ScriptPath, "Script path", "", "Path to script file")
REFL_FIELD(CSharpScript, std::string, Class, "Entry classname", "", "Path to script file")
REFL_END