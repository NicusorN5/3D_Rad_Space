#pragma once
#include "../IUpdateable.hpp"
#include "../Game.hpp"
#include "../IObject.hpp"

namespace Engine3DRadSpace::Scripting
{
	class DLLEXPORT IScript: public IUpdateable
	{
	protected:
		/// <summary>
		/// The object that manages this IScript instance.
		/// </summary>
		IObject* object = nullptr;

		IScript() = default;

		IScript(const IScript&) = delete;
		IScript(IScript&&) = default;

		IScript& operator=(const IScript&) = delete;
		IScript& operator=(IScript&&) = default;
	public:
		/// <summary>
		/// Scripts aren't run by the ObjectList class, but by a ScriptEngine class.
		/// </summary>
		int Priority = 0;

		/// <summary>
		/// Called when this is added into the ScriptEngine.
		/// </summary>
		virtual void Start() = 0;

		/// <summary>
		/// Called when this is removed from the ScriptEngine.
		/// </summary>
		virtual void End() = 0;

		auto operator<=>(const IScript&) const = default;

		~IScript() = default;
	};

	using IScriptInstance = std::shared_ptr<IScript>;
}