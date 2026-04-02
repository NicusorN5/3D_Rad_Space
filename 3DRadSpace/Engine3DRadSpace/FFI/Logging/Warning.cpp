#include "Warning.h"
#include "../../Logging/Warning.hpp"

using namespace Engine3DRadSpace::Logging;

void E3DRSP_SetLastWarning(const E3DRSP_Warning* warning)
{
	SetLastWarning(Warning(
		warning->Code,
		warning->Details,
		warning->Severity,
		warning->Extra
	));
}