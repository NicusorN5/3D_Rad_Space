#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Polymorphic base for all services used by the engine.
	/// </summary>
	class E3DRSP_CORE_EXPORT IService
	{
	public:
		virtual ~IService() = default;
	};
}