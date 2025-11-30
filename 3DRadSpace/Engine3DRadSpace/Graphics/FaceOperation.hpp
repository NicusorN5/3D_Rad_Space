#pragma once
#include "StencilOperation.hpp"
#include "ComparisonFunction.hpp"

namespace Engine3DRadSpace::Graphics
{
	struct FaceOperation
	{
		StencilOperation StencilFail;
		StencilOperation DepthFail;
		StencilOperation PassOp;
		ComparisonFunction Function;
	};
}