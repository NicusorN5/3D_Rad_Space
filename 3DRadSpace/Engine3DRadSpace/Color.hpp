#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents a Unit RGBA color.
	/// </summary>
	struct DLLEXPORT Color
	{
		float R;
		float G;
		float B;
		float A;

		/// <summary>
		/// Constructs a color from 4 components.
		/// </summary>
		/// <param name="r">Red component.</param>
		/// <param name="g">Green component.</param>
		/// <param name="b">Blue component.</param>
		/// <param name="a">Transparency component, called alpha.</param>
		constexpr Color(float r = 0.00f, float g = 0.00f, float b = 0.00f, float a = 1.00f) : R(r), G(g), B(b), A(a) {};
		/// <summary>
		/// Constructs a color from RBGA values made of unsigned 8-bytes numbers.
		/// </summary>
		/// <param name="r">Red component.</param>
		/// <param name="g">Green component.</param>
		/// <param name="b">Blue component.</param>
		/// <param name="a">Transparency component, called alpha.</param>
		/// <returns>Unit RGBA color.</returns>
		static Color FromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		/// <summary>
		/// Comptes a Hadamard product between two colors.
		/// </summary>
		/// <param name="c">Color</param>
		/// <returns>*this * c</returns>
		constexpr Color operator *(const Color& c) const noexcept;
		/// <summary>
		/// Computes a
		/// </summary>
		/// <param name="c"></param>
		/// <returns></returns>
		constexpr Color& operator *=(const Color& c) noexcept;

		constexpr float operator[](int i) const;

		friend auto operator <=>(const Color& a, const Color& b) noexcept = default;
	};

	/// <summary>
	/// This namespace contains a set of predefined colors.
	/// </summary>
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
