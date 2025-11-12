#pragma once

namespace Engine3DRadSpace::Graphics
{
    enum class Blend
    {
        Zero = 0,
        One,
        SourceColor,
        InverseSourceColor,
        SourceAlpha,
        InverseSourceAlpha,
        DestinationAlpha,
        InverseDestinationAlpha,
        DestinationColor,
        InverseDestinationColor,
        SourceAlphaSat,
        BlendFactor,
        InverseBlendFactor,
        Source1Color,
        Source1InverseColor,
        Source1Alpha,
        InverseSource1Alpha
    };
}