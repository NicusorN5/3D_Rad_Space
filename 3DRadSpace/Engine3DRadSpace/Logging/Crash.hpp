#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Logging
{
	void E3DRSP_LOGGING_EXPORT ReportCrashToFile(const std::exception& e, const std::stacktrace& stacktrace);
}