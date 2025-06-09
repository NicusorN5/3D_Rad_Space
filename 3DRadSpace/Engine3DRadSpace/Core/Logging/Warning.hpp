#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Logging
{
	struct E3DRSP_CORE_EXPORT Warning
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

	void E3DRSP_CORE_EXPORT SetLastWarning(const Warning &warning);
	void E3DRSP_CORE_EXPORT SetLastWarning(const std::string &warning_text);
	void E3DRSP_CORE_EXPORT DefaultWarningHandler(const Warning &warning);
}
