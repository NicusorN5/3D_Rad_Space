#include "UnknownVariable.h"
#include "../../Reflection/UnknownVariable.hpp"

using namespace Engine3DRadSpace::Reflection;

E3DRSP_IReflectedField E3DRSP_UnknownVariable_Create(
	size_t offset,
	size_t size,
	const char* name,
	const char* desc
)
{
	return new UnknownVariable(offset, size, name, desc);
}