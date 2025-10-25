#pragma once
#include "GraphicsDevice.hpp"
#include "IDepthStencilState.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT DepthStencilState : public IDepthStencilState
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _state;
#endif
		unsigned int _stencilRef;
		void _debugInfo();
		explicit DepthStencilState(GraphicsDevice* device, std::monostate cpy);
	public:
		explicit DepthStencilState(GraphicsDevice *device);

		DepthStencilState(
			GraphicsDevice *device,
			bool EnableDepth, 
			DepthWriteMask Mask, 
			ComparisonFunction Function,
			bool EnableStencil,
			uint8_t ReadMask,
			uint8_t WriteMask,
			FaceOperation FrontFace,
			FaceOperation BackFace
		);

		DepthStencilState(DepthStencilState &) = delete;
		DepthStencilState(DepthStencilState &&state) noexcept = default;

		DepthStencilState& operator=(DepthStencilState &) = delete;
		DepthStencilState &operator=(DepthStencilState &&state) noexcept = default;

		unsigned int StencilRef() const noexcept override;
		void* GetHandle() const noexcept override;

		static DepthStencilState DepthDefault(GraphicsDevice* device);
		static DepthStencilState DepthNone(GraphicsDevice *device);
		static DepthStencilState DepthRead(GraphicsDevice *device);

		static DepthStencilState DepthReverseZ(GraphicsDevice *device);
		static DepthStencilState DepthReadReverseZ(GraphicsDevice *device);

		~DepthStencilState() = default;

		friend class GraphicsDevice;
	};
}