#pragma once

namespace Engine3DRadSpace::Graphics
{
	enum class StencilOperation
	{
		Keep = 1,
		Zero = 2,
		Replace = 3,
		IncrementClamp = 4,
		DecrementClamp = 5,
		Invert = 6,
		IncrementWrap = 7,
		DecrementWrap = 8
	};
}