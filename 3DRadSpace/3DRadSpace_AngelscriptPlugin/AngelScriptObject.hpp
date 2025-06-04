#pragma once
#include <Engine3DRadSpace\Objects\IObject.hpp>
#include <Engine3DRadSpace\Reflection\Reflection.hpp>

namespace Engine3DRadSpace_Angelscript
{
	/// <summary>
	/// A script object handing a AngelScript source.
	/// </summary>
	class AngelScriptObject : public Engine3DRadSpace::IObject
	{
	public:
		AngelScriptObject(const std::string& name, bool enabled, const std::string& source);
	};
}

REFL_FWD(AngelScriptObject)