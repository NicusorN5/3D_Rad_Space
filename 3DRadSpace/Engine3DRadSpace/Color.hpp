/// ------------------------------------------------------------------------------------------------
/// File:   Color.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	struct DLLEXPORT Color
	{
		float R;
		float G;
		float B;
		float A;

		constexpr Color(float r = 0.00f, float g = 0.00f, float b = 0.00f, float a = 1.00f) : R(r), G(g), B(b), A(a) {};
		static Color FromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		constexpr Color operator *(const Color& c) const noexcept;
		constexpr Color& operator *=(const Color& c) noexcept;

		constexpr float operator[](int i) const;

		friend auto operator <=>(const Color& a, const Color& b) noexcept = default;
	};
	namespace Colors
	{
		constexpr Color White = {1.0f, 1.0f, 1.0f, 1.0f};
		constexpr Color Red = {1.0f, 0.0f, 0.0f, 1.0f};
		constexpr Color Green = {0.0f, 1.0f, 0.0f, 1.0f};
		constexpr Color Blue = {0.0f, 0.0f, 1.0f, 1.0f};
		constexpr Color Black = {0.0f, 0.0f, 0.0f, 1.0f};
		constexpr Color Gray = {0.5f, 0.5f, 0.5f, 1.0f};
		constexpr Color DarkGray = {0.25f, 0.25f, 0.25f, 1.0f};
		constexpr Color Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
		constexpr Color Pink = { 1.0f, 0.0f, 1.0f, 1.0f };
		constexpr Color Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
		constexpr Color CornflowerBlue = {0.392f, 0.584f, 0.929f, 1.0f};
		//TODO: Add more colors.
	};
}
