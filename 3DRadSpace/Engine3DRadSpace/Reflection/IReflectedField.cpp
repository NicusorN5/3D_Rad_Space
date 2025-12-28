#include "IReflectedField.hpp"
#include "IReflectedField.h"

using namespace Engine3DRadSpace::Reflection;

IReflectedField::IReflectedField(
	size_t offset,
	size_t size,
	const std::string& name, 
	const std::string& desc,
	const std::type_info& info
) :
	_typeHash(info.hash_code()),
	_typeIndex(info),
	_size(size),
	_offset(offset), 
	_name(name), 
	_desc(desc)
{
}

const size_t IReflectedField::TypeHash() const noexcept
{
	return _typeHash;
}

const std::string& IReflectedField::FieldName() const noexcept
{
	return _name;
}

const std::string& IReflectedField::FieldDesc() const noexcept
{
	return _desc;
}

const size_t Engine3DRadSpace::Reflection::IReflectedField::TypeSize() const noexcept
{
	return _size;
}

const ptrdiff_t Engine3DRadSpace::Reflection::IReflectedField::FieldOffset() const noexcept
{
	return this->_offset;
}

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