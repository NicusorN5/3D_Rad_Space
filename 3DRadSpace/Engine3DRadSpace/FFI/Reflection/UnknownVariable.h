#pragma once
#include "IReflectedField.h"

extern "C" E3DRSP_REFLECTION_EXPORT E3DRSP_IReflectedField E3DRSP_UnknownVariable_Create(
	size_t offset,
	size_t size,
	const char* name,
	const char* desc
);