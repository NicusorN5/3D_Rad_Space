#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents how a image can be flipped.
	/// </summary>
	enum class FlipMode : uint8_t
	{
		None = 0,
		FlipHorizontally = 0b1,
		FlipVertically = 0b10,
		FlipHorizontallyAndVertically = 0b11,
	};

	/// <summary>
	/// Bitwise AND operator between two FlipModes.
	/// </summary>
	/// <param name="a">FlipMode</param>
	/// <param name="b">FlipMode</param>
	/// <returns>a * b</returns>
	FlipMode DLLEXPORT operator&(FlipMode a, FlipMode b);
	/// <summary>
	/// Bitwise OR operator between two FlipModes.
	/// </summary>
	/// <param name="a">FlipMode</param>
	/// <param name="b">FlipMode</param>
	/// <returns>a + b</returns>
	FlipMode DLLEXPORT operator|(FlipMode a, FlipMode b);
}