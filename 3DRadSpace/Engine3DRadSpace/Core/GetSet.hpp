#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	template<typename T, typename C, auto FnGet, auto FnSet>
	class GetSet
	{
		C* _class;
	public:
		using Type = T;
		using Class = C;
		using Setter = decltype(FnGet);
		using Getter = decltype(FnSet);
		using ThisT = GetSet<T, C, FnGet, FnSet>;

		GetSet(C* instance) :
			_class(instance)
		{
		}

		GetSet(C* instance, const T& defaultValue) : GetSet(instance)
		{
			Set(defaultValue);
		}

		T Get() //noexcept(noexcept(FnGet))
		{
			return (_class->*FnGet)();
		}

		GetSet& operator=(const T& value)
		{
			_class != nullptr ? Set(value) : throw std::exception("null ptr");
		}

		void Set(const T& value) noexcept(noexcept(FnSet))
		{
			(_class->*FnSet)(value);
		}

		operator bool() const noexcept
		{
			return _class != nullptr;
		}
	};
}