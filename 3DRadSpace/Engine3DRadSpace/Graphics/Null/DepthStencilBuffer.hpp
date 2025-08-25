#pragma once
#include "../IDepthStencilBuffer.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class GraphicsDevice;
	class Texture2D;

	class E3DRSP_GRAPHICS_NULL_EXPORT DepthStencilBuffer final : public IDepthStencilBuffer
	{
	public:
		explicit DepthStencilBuffer(GraphicsDevice* device);

		explicit DepthStencilBuffer(GraphicsDevice* device, unsigned x, unsigned y);

		DepthStencilBuffer(DepthStencilBuffer &) = delete;
		DepthStencilBuffer(DepthStencilBuffer &&buff) noexcept = default;

		DepthStencilBuffer &operator=(DepthStencilBuffer &) = delete;
		DepthStencilBuffer &operator=(DepthStencilBuffer &&buff) noexcept = default;

		void* GetViewHandle() const noexcept override;
		void* GetDepthTextureHandle() const noexcept override;
		Texture2D* GetDepthTexture() const noexcept override;

		void* GetHandle() const noexcept override;

		Texture2D CloneDepthTexture() override;
	};
}