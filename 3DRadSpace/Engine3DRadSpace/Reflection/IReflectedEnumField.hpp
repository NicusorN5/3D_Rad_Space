#pragma once
#include "ReflectedField.hpp"
#include "ReflectedEnum.hpp"

namespace Engine3DRadSpace::Reflection
{
	template<typename E>
	concept ReflectableEnum = std::is_enum_v<E>;

	class DLLEXPORT IReflectedEnumField: public IReflectedField
	{
	protected:
		IReflectedEnumField() = default;
		IReflectedEnumField(const IReflectedEnumField&) = default;
		IReflectedEnumField(IReflectedEnumField&&) = default;

		IReflectedEnumField& operator=(const IReflectedEnumField&) = default;
		IReflectedEnumField& operator=(IReflectedEnumField&&) = default;
	public:
		virtual ReflectedEnum GetEnum() = 0;
		~IReflectedEnumField() = default;
	};
}