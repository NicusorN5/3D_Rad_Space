/// ------------------------------------------------------------------------------------------------
/// File:   IInitiializable.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once

namespace Engine3DRadSpace
{
	class DLLEXPORT IInitiializable
	{
	public:
		virtual void Initialize() = 0;
		inline virtual ~IInitiializable() = default;
	};
}