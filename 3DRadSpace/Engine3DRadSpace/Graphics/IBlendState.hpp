#pragma once
#include "IGPUResource.hpp"
#include "RenderTargetBlendState.hpp"

namespace Engine3DRadSpace::Graphics
{
    /// <summary>
    /// Represents blend state GPU handles.
    /// </summary>
    class E3DRSP_GRAPHICS_EXPORT IBlendState : public IGPUResource
    {
    public:
        /// <summary>
        /// Gets the blend factor.
        /// </summary>
        /// <returns>Blend factor.</returns>
        virtual Math::Color BlendFactor() const noexcept = 0;
        virtual unsigned int SampleMask() const noexcept = 0;
    };
}
