#include "IReflectedField.hpp"

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
