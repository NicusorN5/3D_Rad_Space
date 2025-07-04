#pragma once
#include "../IScriptBuilder.hpp"

namespace Engine3DRadSpace::Scripting::CPP
{
	class E3DRSP_SCRIPTING_EXPORT CppScriptBuilder : public IScriptBuilder
	{
	public:
		CppScriptBuilder();

		// Inherited via IScriptBuilder
		bool IsAvailable() const override;
		const std::string Language() const override;
		CompileReturn Compile(const std::filesystem::path& scriptPath) override;
	};
}