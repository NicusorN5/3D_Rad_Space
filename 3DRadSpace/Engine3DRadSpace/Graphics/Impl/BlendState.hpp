#pragma once
#include "../IBlendState.hpp"
#include "../Null/BlendState.hpp"
#include "../DirectX11/BlendState.hpp"
#include "../../Math/Color.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_IMPL_EXPORT BlendState
	{
    public:
        explicit BlendState(IGraphicsDevice *device);

        BlendState(IGraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, const RenderTargetBlendState &renderTargetBlendState);
  
        BlendState(IGraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, std::array<RenderTargetBlendState, 8> renderTargetBlendStates);

        BlendState(BlendState &) = delete;
        BlendState(BlendState &&blend) noexcept = default;

        BlendState &operator=(BlendState &) = delete;
        BlendState &operator=(BlendState &&blend) noexcept = default;

        Math::Color BlendFactor() const noexcept override;
        unsigned int SampleMask() const noexcept override;

        void* GetHandle() const noexcept override;

        virtual IGraphicsDevice* GetGraphicsDevice() const noexcept override;

        ~BlendState() = default;

        static BlendState Opaque(IGraphicsDevice *device);
        static BlendState AlphaBlend(IGraphicsDevice *device);
        static BlendState Additive(IGraphicsDevice *device);
        static BlendState NonPremultiplied(IGraphicsDevice *device);

        static BlendState GetCurrentBlendState(IGraphicsDevice* device);
    };
}
