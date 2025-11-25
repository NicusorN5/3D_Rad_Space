#include "UnknownVariable.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

UnknownVariable::UnknownVariable(
	size_t offset,
	size_t size,
	const std::string& name,
	const std::string& desc
) : IReflectedField(offset, size, name, desc, typeid(void))
{
}

const void* UnknownVariable::Get(void* objPtr) const
{
	return static_cast<void*>(static_cast<std::byte*>(objPtr) + _offset);
}

void UnknownVariable::Set(void* objPtr, const void* value) const
{
	auto ptr = static_cast<void*>(static_cast<std::byte*>(objPtr) + _offset);
	memcpy_s(ptr, _size, value, _size);
}

const void* UnknownVariable::DefaultValue() const
{
	return nullptr;
}

FieldRepresentation UnknownVariable::Representation() const
{
	return { {FieldRepresentationType::Unknown, ""} };
}