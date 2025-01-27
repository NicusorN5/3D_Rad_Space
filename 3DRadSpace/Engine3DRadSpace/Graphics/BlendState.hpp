#pragma once
#include "../GraphicsDevice.hpp"

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

    enum class BlendOperation
    {
        Add,
        Substract,
        ReverseSubstract,
        Minimum,
        Maximum,
    };

    enum class ColorWriteEnable
    {
        Red,
        Greed,
        Blue,
        Alpha,
        All
    };

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

	class DLLEXPORT BlendState
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11BlendState> _blendState;
        GraphicsDevice *_device;

        Color _blendFactor = {};
        unsigned int _sampleMask = 0;

        D3D11_BLEND convert3DRSPBlend_toDX11(Blend b);
        D3D11_BLEND_OP convert3DRSPBlendOp_toDX11(BlendOperation op);
        D3D11_COLOR_WRITE_ENABLE convert3DRSPColorWrite_toDX11(ColorWriteEnable flag);
#endif
        void _debugInfo();
        explicit BlendState(GraphicsDevice* device, std::monostate cpy);
	public:
		/// <summary>
		/// Craetes a default blend state.
		/// </summary>
		/// <param name="device">Graphics device required to create the blend state.</param>
		explicit BlendState(GraphicsDevice *device);

        BlendState(GraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, const RenderTargetBlendState &renderTargetBlendState);
        BlendState(GraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, std::array<RenderTargetBlendState, 8> renderTargetBlendStates);

        BlendState(BlendState &) = delete;
        BlendState(BlendState &&blend) noexcept = default;

        BlendState &operator=(BlendState &) = delete;
        BlendState &operator=(BlendState &&blend) noexcept = default;

        Color BlendFactor() const noexcept;
        unsigned int SampleMask() const noexcept;
        void* GetHandle() const noexcept;

        ~BlendState() = default;

        static BlendState Opaque(GraphicsDevice *device);
        static BlendState AlphaBlend(GraphicsDevice *device);
        static BlendState Additive(GraphicsDevice *device);
        static BlendState NonPremultiplied(GraphicsDevice *device);

        static BlendState GetCurrentBlendState(GraphicsDevice* device);

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}
