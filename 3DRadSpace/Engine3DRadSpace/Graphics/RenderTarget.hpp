#pragma once
#include "Texture2D.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT RenderTarget : public Texture2D
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTarget;
#endif
	protected:
		explicit RenderTarget(GraphicsDevice* device, std::monostate cpy);
		explicit RenderTarget(Internal::AssetUUIDReader r);
	public:
		/// <summary>
		/// Create a render target with the same size as the backbuffer, and the specified format.
		/// </summary>
		/// <param name="device">Graphics context</param>
		/// <param name="format">Texture color format</param>
		RenderTarget(GraphicsDevice *device, PixelFormat format = PixelFormat::R16G16B16A16_Float);
		/// <summary>
		/// Create a render target with specified size and format.
		/// </summary>
		/// <param name="device">Graphics device</param>
		/// <param name="x">Texture width.</param>
		/// <param name="y">Texture height.</param>
		/// <param name="format">Color format.</param>
		RenderTarget(GraphicsDevice* device, unsigned x, unsigned y, PixelFormat format = PixelFormat::R16G16B16A16_Float);

		RenderTarget(const RenderTarget&) = delete;
		RenderTarget& operator=(const RenderTarget&) = delete;

		RenderTarget(RenderTarget&&) noexcept = default;
		RenderTarget& operator=(RenderTarget&&) noexcept = default;

		void* RenderTargetHandle() const noexcept;

		static RenderTarget GetCurrentRenderTarget(GraphicsDevice* device);
		static std::array<RenderTarget*, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> GetCurrentRenderTargets(GraphicsDevice* device);

		~RenderTarget() = default;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}

