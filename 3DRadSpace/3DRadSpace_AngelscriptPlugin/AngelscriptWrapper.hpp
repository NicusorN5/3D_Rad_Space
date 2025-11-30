#pragma once

namespace Engine3DRadSpace::Angelscript
{
	class AngelScriptWrapper final
	{
		void* _engine;
	public:
		AngelScriptWrapper();

		~AngelScriptWrapper();
	};
}