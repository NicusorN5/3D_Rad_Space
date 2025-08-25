#pragma once
#include "../IBlendState.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class E3DRSP_GRAPHICS_NULL_EXPORT BlendState final : public IBlendState
	{
    public:
        explicit BlendState(GraphicsDevice *device);

        BlendState(GraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, const RenderTargetBlendState &renderTargetBlendState);
  
        BlendState(GraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, std::array<RenderTargetBlendState, 8> renderTargetBlendStates);

        BlendState(BlendState &) = delete;
        BlendState(BlendState &&blend) noexcept = default;

        BlendState &operator=(BlendState &) = delete;
        BlendState &operator=(BlendState &&blend) noexcept = default;

        Math::Color BlendFactor() const noexcept override;
        unsigned int SampleMask() const noexcept override;

        void* GetHandle() const noexcept override;

        virtual IGraphicsDevice* GetGraphicsDevice() const noexcept override;

        ~BlendState() = default;

        static BlendState Opaque(GraphicsDevice *device);
        static BlendState AlphaBlend(GraphicsDevice *device);
        static BlendState Additive(GraphicsDevice *device);
        static BlendState NonPremultiplied(GraphicsDevice *device);

        static BlendState GetCurrentBlendState(GraphicsDevice* device);
    };
}
