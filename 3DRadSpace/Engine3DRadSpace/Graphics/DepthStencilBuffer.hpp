#pragma once
#include "../GraphicsDevice.hpp"
#include "Texture2D.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT DepthStencilBuffer
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthView;
#endif
		std::unique_ptr<Texture2D> _depthTexture;
		GraphicsDevice *_device;
		void _createDepthTexture();
	public:
		explicit DepthStencilBuffer(GraphicsDevice* device);

		DepthStencilBuffer(DepthStencilBuffer &) = delete;
		DepthStencilBuffer(DepthStencilBuffer &&buff) noexcept = default;

		DepthStencilBuffer &operator=(DepthStencilBuffer &) = delete;
		DepthStencilBuffer &operator=(DepthStencilBuffer &&buff) noexcept = default;

		void* GetViewHandle() const noexcept;
		void* GetDepthTextureHandle() const noexcept;
		
		Texture2D* GetDepthTexture() const noexcept;

		~DepthStencilBuffer() = default;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}
