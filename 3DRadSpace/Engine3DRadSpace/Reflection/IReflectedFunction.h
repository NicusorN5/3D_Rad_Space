#pragma once
#include "IReflectedField.h"

typedef void* E3DRSP_IReflectedFunction;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_REFLECTION_EXPORT const char* E3DRSP_IReflectedFunction_Signature(E3DRSP_IReflectedFunction func);
	E3DRSP_REFLECTION_EXPORT void E3DRSP_IReflectedFunction_Invoke(
		E3DRSP_IReflectedFunction func,
		void* self,
		void* outArg,
		void** args,
		size_t numArgs
	);
#ifdef __cplusplus
}
#endif // __cplusplus