#pragma once
#include "../IRasterizerState.hpp"
#include "../RasterizerCullMode.hpp"
#include "../RasterizerFillMode.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class GraphicsDevice;

	class E3DRSP_GRAPHICS_EXPORT RasterizerState : public IRasterizerState
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _rasterizerState;
		void _debugInfo();
#endif
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
	};
}