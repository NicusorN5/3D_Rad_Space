#include "ReflectedEnum.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

const std::string Engine3DRadSpace::Reflection::ReflectedEnum::EnumName() const noexcept
{
	return _enumName;
}

const size_t ReflectedEnum::NumberOfEntries() const noexcept
{
	return _entries.size() - 1;
}

const EnumEntry ReflectedEnum::operator[](unsigned entryId) const noexcept
{
	return _entries[entryId];
}

const size_t Engine3DRadSpace::Reflection::ReflectedEnum::TypeHashCode() const noexcept
{
	return _typeHash;
}

std::vector<EnumEntry>::iterator ReflectedEnum::begin()
{
	return _entries.begin();
}

std::vector<EnumEntry>::iterator ReflectedEnum::end()
{
	return std::prev(_entries.end());
}
