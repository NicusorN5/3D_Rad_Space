#pragma once
#include "../IRasterizerState.hpp"
#include "../RasterizerFillMode.hpp"
#include "../RasterizerCullMode.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class E3DRSP_GRAPHICS_NULL_EXPORT RasterizerState final : public IRasterizerState
	{
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

		void* GetHandle() const noexcept;

		static RasterizerState CullNone(GraphicsDevice *device);
		static RasterizerState CullClockwise(GraphicsDevice *device);
		static RasterizerState CullCounterClockwise(GraphicsDevice *device);
		static RasterizerState Wireframe(GraphicsDevice *device);

		std::unique_ptr<IRasterizerState> GetCurrentRasterizerState(IGraphicsDevice* device) override;

		~RasterizerState() = default;

		friend class GraphicsDevice;
	};
}