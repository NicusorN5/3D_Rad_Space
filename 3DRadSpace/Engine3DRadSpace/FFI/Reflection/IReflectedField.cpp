#include "IReflectedField.h"
#include "../../Reflection/IReflectedField.hpp"

using namespace Engine3DRadSpace::Reflection;

const size_t E3DRSP_IReflectedField_TypeHash(E3DRSP_IReflectedField field)
{
	return reinterpret_cast<IReflectedField*>(field)->TypeHash();
}

const char* E3DRSP_IReflectedField_FieldName(E3DRSP_IReflectedField field)
{
	return reinterpret_cast<IReflectedField*>(field)->FieldName().c_str();
}

const char* E3DRSP_IReflectedField_FieldDesc(E3DRSP_IReflectedField field)
{
	return reinterpret_cast<IReflectedField*>(field)->FieldDesc().c_str();
}

const size_t E3DRSP_IReflectedField_TypeSize(E3DRSP_IReflectedField field)
{
	return reinterpret_cast<IReflectedField*>(field)->TypeSize();
}

const ptrdiff_t E3DRSP_IReflectedField_FieldOffset(E3DRSP_IReflectedField field)
{
	return reinterpret_cast<IReflectedField*>(field)->FieldOffset();
}

const void* E3DRSP_IReflectedField_Get(E3DRSP_IReflectedField field, void* objPtr)
{
	return reinterpret_cast<IReflectedField*>(field)->Get(objPtr);
}

void E3DRSP_IReflectedField_Set(E3DRSP_IReflectedField field, void* objPtr, const void* value)
{
	reinterpret_cast<IReflectedField*>(field)->Set(objPtr, value);
}

const void* E3DRSP_IReflectedField_DefaultValue(E3DRSP_IReflectedField field)
{
	return reinterpret_cast<IReflectedField*>(field)->DefaultValue();
}

void E3DRSP_IReflectedField_Destroy(E3DRSP_IReflectedField field)
{
	delete reinterpret_cast<IReflectedField*>(field);
}