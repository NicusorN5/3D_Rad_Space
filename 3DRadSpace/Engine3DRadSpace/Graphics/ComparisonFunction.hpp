#pragma once

namespace Engine3DRadSpace::Graphics
{
	enum class ComparisonFunction : int
	{
		Never = 1,
		Less,
		Equal,
		LessEqual,
		Greater,
		NotEqual,
		GreaterEqual,
		Always,
	};
}