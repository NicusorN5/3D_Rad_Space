#pragma once
#include "Blend.h"
#include "BlendOperation.h"
#include "ColorWriteEnable.h"

struct E3DRSP_RenderTargetBlendState
{
    _Bool EnableBlending;
    E3DRSP_Blend SourceBlend;
    E3DRSP_Blend DestinationBlend;
    E3DRSP_BlendOperation BlendOp;
    E3DRSP_Blend SourceBlendAlpha;
    E3DRSP_Blend DestinationBlendAlpha;
    E3DRSP_BlendOperation BlendOpAlpha;
    E3DRSP_ColorWriteEnable WriteMask;
};