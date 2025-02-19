/// ------------------------------------------------------------------------------------------------
/// File:   Reflection/ReflectedEnum.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "ReflectedObject.hpp"
#include "..\Algorithms\FixedArray.hpp"
#include "../Tag.hpp"

namespace Engine3DRadSpace::Reflection
{
#pragma warning(push)
#pragma warning(disable:26495)
	struct EnumEntry
	{
		std::string VisibleName;
		int Value;
	};
#pragma warning(pop)

	class DLLEXPORT ReflectedEnum
	{
		std::string _enumName;
		Algorithms::FixedArray<EnumEntry> _entries;
		size_t _typeHash;
	public:
		template<typename E> requires std::is_enum_v<E>
		ReflectedEnum(Tag<E> dummy, const std::string& name, std::initializer_list<EnumEntry> entries) :
			_enumName(name),
			_entries(entries),
			_typeHash(typeid(E).hash_code())
		{
		}

		const std::string EnumName() const noexcept;
		const size_t NumberOfEntries() const noexcept;
		const EnumEntry operator[](unsigned entryId) const noexcept;
		const size_t TypeHashCode() const noexcept;

		Algorithms::FixedArray<EnumEntry>::Iterator begin();
		Algorithms::FixedArray<EnumEntry>::Iterator end();
	};
}