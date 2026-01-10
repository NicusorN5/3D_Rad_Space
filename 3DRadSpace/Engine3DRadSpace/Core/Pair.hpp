#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	template<typename T1, typename T2>
	struct Pair
	{
		using FirstType = T1;
		using SecondType = T2;

		T1 First;
		T2 Second;

		constexpr Pair() = default;
		constexpr Pair(const T1& first, const T2& second) : First(first), Second(second) {}
		constexpr Pair(T&& first, T2&& second) : First(std::move(first)), Second(std::move(second)) {}

		constexpr auto operator <=>(const Pair&) const = default;
	};
}