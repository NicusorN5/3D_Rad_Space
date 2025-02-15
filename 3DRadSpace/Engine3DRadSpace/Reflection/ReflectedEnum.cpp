/// ------------------------------------------------------------------------------------------------
/// File:   Reflection/ReflectedEnum.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "ReflectedEnum.hpp"

using namespace Engine3DRadSpace::Reflection;
using namespace Engine3DRadSpace::Algorithms;

const std::string Engine3DRadSpace::Reflection::ReflectedEnum::EnumName() const noexcept
{
	return _enumName;
}

const size_t ReflectedEnum::NumberOfEntries() const noexcept
{
	return _entries.Size() - 1;
}

const EnumEntry ReflectedEnum::operator[](unsigned entryId) const noexcept
{
	return _entries[entryId];
}

const size_t Engine3DRadSpace::Reflection::ReflectedEnum::TypeHashCode() const noexcept
{
	return _typeHash;
}

FixedArray<EnumEntry>::Iterator ReflectedEnum::begin()
{
	return _entries.begin();
}

FixedArray<EnumEntry>::Iterator ReflectedEnum::end()
{
	return std::prev(_entries.end());
}
