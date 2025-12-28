#pragma once
#include "StencilOperation.h"
#include "ComparisonFunction.h"

typedef struct E3DRSP_FaceOperation
{
	E3DRSP_StencilOperation StencilFail;
	E3DRSP_StencilOperation DepthFail;
	E3DRSP_StencilOperation PassOp;
	E3DRSP_ComparisonFunction Function;
} E3DRSP_FaceOperation;