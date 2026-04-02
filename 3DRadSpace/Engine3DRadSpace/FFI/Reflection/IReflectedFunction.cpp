#include "IReflectedFunction.h"
#include "../../Reflection/IReflectedFunction.hpp"

using namespace Engine3DRadSpace::Reflection;

const char* E3DRSP_IReflectedFunction_Signature(E3DRSP_IReflectedFunction func)
{
	auto f = reinterpret_cast<IReflectedFunction*>(func);
	return f->Signature().c_str();
}

void E3DRSP_IReflectedFunction_Invoke(
	E3DRSP_IReflectedFunction func,
	void* self,
	void* outArg,
	void** args,
	size_t numArgs
)
{
	auto f = reinterpret_cast<IReflectedFunction*>(func);
	f->Invoke(outArg, self, std::span<void*>(args, numArgs));
}