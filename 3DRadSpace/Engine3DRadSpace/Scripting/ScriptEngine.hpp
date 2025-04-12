#pragma once
#include "IScript.hpp"

namespace Engine3DRadSpace::Scripting
{
	/// <summary>
	/// Manages all scripts.
	/// </summary>
	/// <remarks>
	/// This class is non-copyable, non-moveable, as one instance per application is expected, usually owned by a Game class.
	/// </remarks>
	class DLLEXPORT ScriptEngine
	{
	public:
		ScriptEngine() = default;

		ScriptEngine(const ScriptEngine&) = delete;
		ScriptEngine(ScriptEngine&&) = delete;

		ScriptEngine& operator=(const ScriptEngine&) = delete;
		ScriptEngine& operator=(ScriptEngine&&) = delete;

		/// <summary>
		/// A list of ref-counted instances of scripts.
		/// </summary>
		std::vector<std::shared_ptr<IScript>> Scripts;

		void Sort();
	};
}