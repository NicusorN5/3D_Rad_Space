#pragma once
#include "../IScript.hpp"

namespace Engine3DRadSpace::Scripting::CSharp
{
	class __declspec(dllexport) CSharpScriptInstance : public IScript
	{
	public:
		CSharpScriptInstance();
	};
}