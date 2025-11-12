#pragma once
#include "../IRenderTarget.hpp"
#include "../IGraphicsDevice.hpp"
#include "Texture2D.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class E3DRSP_GRAPHICS_NULL_EXPORT RenderTarget final : public IRenderTarget, public Texture2D
	{
	public:
		RenderTarget(IGraphicsDevice *device, PixelFormat format = PixelFormat::R16G16B16A16_Float);
		RenderTarget(IGraphicsDevice* device, unsigned x, unsigned y, PixelFormat format = PixelFormat::R16G16B16A16_Float);

		RenderTarget(const RenderTarget&) = delete;
		RenderTarget& operator=(const RenderTarget&) = delete;

		RenderTarget(RenderTarget&&) noexcept = default;
		RenderTarget& operator=(RenderTarget&&) noexcept = default;

		void* RenderTargetHandle() const noexcept override;

		static RenderTarget GetCurrentRenderTarget(IGraphicsDevice* device);
		static std::array<RenderTarget*, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> GetCurrentRenderTargets(IGraphicsDevice* device);

		~RenderTarget() = default;

		friend class GraphicsDevice;
	};
}