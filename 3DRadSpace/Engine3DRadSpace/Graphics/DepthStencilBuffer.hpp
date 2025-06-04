#pragma once
#include "GraphicsDevice.hpp"
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

		D3D11_TEXTURE2D_DESC _defaultDepthDesc(unsigned x, unsigned y);
		D3D11_DEPTH_STENCIL_VIEW_DESC _defaultDepthViewDesc();
		D3D11_SHADER_RESOURCE_VIEW_DESC _defaultShaderViewDesc();
#endif
		std::unique_ptr<Texture2D> _depthTexture;
		GraphicsDevice *_device;
		void _createDepthTexture(unsigned x, unsigned y);
	public:
		/// <summary>
		/// Creates a depth stencil buffer.
		/// </summary>
		/// <param name="device">Graphics device.</param>
		explicit DepthStencilBuffer(GraphicsDevice* device);

		/// <summary>
		/// Creates a depth stencil buffer with specified sizes.
		/// </summary>
		/// <param name="device">Graphics device.</param>
		/// <param name="x">Width.</param>
		/// <param name="y">Height.</param>
		explicit DepthStencilBuffer(GraphicsDevice* device, unsigned x, unsigned y);

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

		Texture2D CloneDepthTexture();

		~DepthStencilBuffer() = default;

		friend class GraphicsDevice;
	};
}
