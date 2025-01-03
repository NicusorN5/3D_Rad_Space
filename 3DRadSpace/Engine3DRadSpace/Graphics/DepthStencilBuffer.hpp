#pragma once
#include "../GraphicsDevice.hpp"
#include "DepthStencilState.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Texture2D;
	class DLLEXPORT DepthStencilBuffer
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthTexture;
#endif
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

		std::unique_ptr<Texture2D> GetDepthTexture() const;

		~DepthStencilBuffer() = default;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}
