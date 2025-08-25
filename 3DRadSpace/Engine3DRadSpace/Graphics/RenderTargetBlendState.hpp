#pragma once
#include "Blend.hpp"
#include "BlendOperation.hpp"
#include "ColorWriteEnable.hpp"

namespace Engine3DRadSpace::Graphics
{
    struct RenderTargetBlendState
    {
        bool EnableBlending;
        Blend SourceBlend;
        Blend DestinationBlend;
        BlendOperation BlendOp;
        Blend SourceBlendAlpha;
        Blend DestinationBlendAlpha;
        BlendOperation BlendOpAlpha;
        ColorWriteEnable WriteMask;
    };
}