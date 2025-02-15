/// ------------------------------------------------------------------------------------------------
/// File:   Logging/Warning.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Logging
{
	struct DLLEXPORT Warning
	{
		const std::string Details;
		int32_t Code;
		int Severity;
		const void *Extra;

		Warning(const int32_t code, const int severity);
		Warning(const int32_t code, const std::string& details, const int severity, const void* extra = nullptr);
	};

	typedef void (*FuncWarningHandler)(const Warning& warning);
	extern FuncWarningHandler WarningHandler;

	void DLLEXPORT SetLastWarning(const Warning &warning);
	void DLLEXPORT SetLastWarning(const std::string &warning_text);
	void DLLEXPORT DefaultWarningHandler(const Warning &warning);
}
