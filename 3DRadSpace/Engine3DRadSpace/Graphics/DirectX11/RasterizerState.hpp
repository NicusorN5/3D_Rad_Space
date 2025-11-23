#pragma once
#include "../IRasterizerState.hpp"
#include "../RasterizerCullMode.hpp"
#include "../RasterizerFillMode.hpp"
#include "DirectX11.h"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class GraphicsDevice;

	class E3DRSP_GRAPHICS_DX11_EXPORT RasterizerState : public IRasterizerState
	{
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _rasterizerState;
		void _debugInfo();

		RasterizerState(GraphicsDevice* device, std::monostate cpy);
	public:

		explicit RasterizerState(
			GraphicsDevice *device,
			RasterizerFillMode filling = RasterizerFillMode::Solid,
			RasterizerCullMode culling = RasterizerCullMode::CullBack,
			bool switchFrontBack = false,
			int depthBias = 0,
			float depthBiasClamp = 0,
			float slopeScaleDepthBias = 0,
			bool depthClip = false,
			bool scissor = false,
			bool multisample = false,
			bool aaLine = false
		);

		RasterizerState(RasterizerState &) = delete;
		RasterizerState(RasterizerState &&state) noexcept = default;

		RasterizerState &operator =(RasterizerState &) = delete;
		RasterizerState &operator =(RasterizerState &&state) noexcept = default;

		void* GetHandle() const noexcept override;
		virtual IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		static RasterizerState CullNone(GraphicsDevice *device);
		static RasterizerState CullClockwise(GraphicsDevice *device);
		static RasterizerState CullCounterClockwise(GraphicsDevice *device);
		static RasterizerState Wireframe(GraphicsDevice *device);

		std::unique_ptr<IRasterizerState> GetCurrentRasterizerState(IGraphicsDevice* device) override;

		~RasterizerState() = default;

		friend class GraphicsDevice;
		friend class GraphicsCommandList;
	};
}