/// ------------------------------------------------------------------------------------------------
/// File:   Logging/Exception.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include <string>
#include "../Libs.hpp"

namespace Engine3DRadSpace::Logging
{
#pragma warning(push)
#pragma warning(disable:4275)
	/// <summary>
	/// Replaces std::exception.
	/// </summary>
	class DLLEXPORT Exception : std::exception
	{
	protected:
		std::string _str;
	public:
		explicit Exception(const std::string &err);

		Exception() = default;
		Exception(Exception&) = default;
		Exception(Exception&&) = default;

		virtual std::string What() const;
		const char* what() const override;
		~Exception() override = default;
	};
#pragma warning(pop)
}

