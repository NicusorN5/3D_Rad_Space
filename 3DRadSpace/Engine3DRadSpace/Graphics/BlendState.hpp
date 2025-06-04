#pragma once
#include "GraphicsDevice.hpp"

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

	/// <summary>
	/// Represents blend state GPU handles.
	/// </summary>
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
        /// <remarks>
        /// Copy constructors are deleted, since creating GPU resources is expensive.
        /// </remarks>
		explicit BlendState(GraphicsDevice *device);

        /// <summary>
        /// Creates a BlendState instance, with specified arguments for the backbuffer.
        /// </summary>
        /// <param name="device">Graphics device.</param>
        /// <param name="alphaCoverage">TODO</param>
        /// <param name="indepedentBlend">TODO</param>
        /// <param name="renderTargetBlendState">Back buffer blend state.</param>
        BlendState(GraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, const RenderTargetBlendState &renderTargetBlendState);
        /// <summary>
        /// Creates a BlendState instance, with specified arguments for all available render targets.
        /// </summary>
        /// <param name="device">Graphics device.</param>
        /// <param name="alphaCoverage"></param>
        /// <param name="indepedentBlend"></param>
        /// <param name="renderTargetBlendStates">Blend states for each render target.</param>
        BlendState(GraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, std::array<RenderTargetBlendState, 8> renderTargetBlendStates);

        BlendState(BlendState &) = delete;
        BlendState(BlendState &&blend) noexcept = default;

        BlendState &operator=(BlendState &) = delete;
        BlendState &operator=(BlendState &&blend) noexcept = default;

        /// <summary>
        /// Gets the blend factor.
        /// </summary>
        /// <returns>Blend factor.</returns>
        Color BlendFactor() const noexcept;
        unsigned int SampleMask() const noexcept;
        /// <summary>
        /// Gets the GPU handle of the blend state, in DX11 it is ID3D11BlendState.
        /// </summary>
        /// <returns>ID3D11BlendState in DX11.</returns>
        void* GetHandle() const noexcept;

        ~BlendState() = default;

        /// <summary>
        /// Creates an opaque blend state.
        /// </summary>
        /// <param name="device">Graphics device handle</param>
        /// <returns>Blend state/</returns>
        static BlendState Opaque(GraphicsDevice *device);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="device"></param>
        /// <returns></returns>
        static BlendState AlphaBlend(GraphicsDevice *device);
        static BlendState Additive(GraphicsDevice *device);
        static BlendState NonPremultiplied(GraphicsDevice *device);

        /// <summary>
        /// Gets the current blend state.
        /// </summary>
        /// <param name="device">Graphics device</param>
        /// <returns>BlendState</returns>
        static BlendState GetCurrentBlendState(GraphicsDevice* device);

		friend class GraphicsDevice;
	};
}
