#pragma once
#include <string>

namespace Engine3DRadSpace::Angelscript
{
	class AngelScriptWrapper final
	{
		void* _engine;
	public:
		AngelScriptWrapper();

		void Call(const std::string& fnName);

		~AngelScriptWrapper();
	};
}