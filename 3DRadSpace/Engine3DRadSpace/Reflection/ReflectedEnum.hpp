#pragma once
#include "ReflectedObject.hpp"
#include "..\Core\Algorithms\FixedArray.hpp"
#include "../Core/Tag.hpp"
#include "EnumEntry.hpp"

namespace Engine3DRadSpace::Reflection
{
	class E3DRSP_REFLECTION_EXPORT ReflectedEnum
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