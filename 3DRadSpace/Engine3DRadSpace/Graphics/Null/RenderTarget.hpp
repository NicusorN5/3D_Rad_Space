#pragma once
#include "../IRenderTarget.hpp"
#include "Texture2D.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class GraphicsDevice;
	class E3DRSP_GRAPHICS_NULL_EXPORT RenderTarget final : public IRenderTarget, public Texture2D
	{
	public:
		RenderTarget(GraphicsDevice*device, PixelFormat format = PixelFormat::R16G16B16A16_Float);
		RenderTarget(GraphicsDevice* device, unsigned x, unsigned y, PixelFormat format = PixelFormat::R16G16B16A16_Float);

		RenderTarget(const RenderTarget&) = delete;
		RenderTarget& operator=(const RenderTarget&) = delete;

		RenderTarget(RenderTarget&&) noexcept = default;
		RenderTarget& operator=(RenderTarget&&) noexcept = default;

		void* RenderTargetHandle() const noexcept override;

		static RenderTarget GetCurrentRenderTarget(GraphicsDevice* device);
		static std::array<RenderTarget*, 8> GetCurrentRenderTargets(GraphicsDevice* device);

		~RenderTarget() = default;

		friend class GraphicsDevice;
	};
}