#pragma once
#include "../GraphicsDevice.hpp"
#include "Texture2D.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents the depth stencil buffer.
	/// </summary>
	/// <remarks>
	/// Since this is a large resource, usually the same size as the backbuffer, copy constructors are removed.
	/// </remarks>
	class DLLEXPORT DepthStencilBuffer
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthView;
#endif
		std::unique_ptr<Texture2D> _depthTexture;
		GraphicsDevice *_device;
		void _createDepthTexture();
	public:
		/// <summary>
		/// Creates a depth stencil buffer.
		/// </summary>
		/// <param name="device">Graphics device.</param>
		explicit DepthStencilBuffer(GraphicsDevice* device);

		DepthStencilBuffer(DepthStencilBuffer &) = delete;
		DepthStencilBuffer(DepthStencilBuffer &&buff) noexcept = default;

		DepthStencilBuffer &operator=(DepthStencilBuffer &) = delete;
		DepthStencilBuffer &operator=(DepthStencilBuffer &&buff) noexcept = default;

		/// <summary>
		/// Gets the native depth stencil view handle.
		/// </summary>
		/// <returns>ID3D11DepthStencilView in DX11.</returns>
		void* GetViewHandle() const noexcept;
		/// <summary>
		/// Gets the depth texture native handle.
		/// </summary>
		/// <returns>ID3D11Texture2D in DX11.</returns>
		void* GetDepthTextureHandle() const noexcept;
		
		/// <summary>
		/// Gets the depth stencil texture.
		/// </summary>
		/// <returns>Depth Stencil texture pointer.</returns>
		Texture2D* GetDepthTexture() const noexcept;

		~DepthStencilBuffer() = default;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}
