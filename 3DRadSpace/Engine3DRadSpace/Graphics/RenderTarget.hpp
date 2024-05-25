#pragma once
#include "Texture2D.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT RenderTarget : public Texture2D
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTarget;
#endif
		RenderTarget(GraphicsDevice* device, std::monostate cpy);
	public:
		RenderTarget(GraphicsDevice *device, PixelFormat format = PixelFormat::R32G32B32A32_Float);
		RenderTarget(GraphicsDevice* device, unsigned x, unsigned y, PixelFormat format = PixelFormat::R32G32B32A32_Float);

		void* RenderTargetHandle() const noexcept;

		static RenderTarget GetCurrentRenderTarget(GraphicsDevice* device);
		static std::array<RenderTarget, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> GetCurrentRenderTargets(GraphicsDevice* device);

		~RenderTarget() = default;

		friend class GraphicsDevice;
	};
}

