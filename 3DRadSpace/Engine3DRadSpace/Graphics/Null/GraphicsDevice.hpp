#pragma once
#include "../IGraphicsDevice.hpp"
#include "../../Math/Color.hpp"
#include "../Viewport.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	/// <summary>
	/// Null GraphicsDevice implementation that doesn't make any GAPI calls.
	/// </summary>
	/// <remarks>
	/// A null graphics device can be used for a headless application, for servers, physics-only simulation, testing, et cetera...
	/// </remarks>
	class E3DRSP_GRAPHICS_NULL_EXPORT GraphicsDevice final : public IGraphicsDevice
	{
	public:
		GraphicsDevice() = delete;
		explicit GraphicsDevice(void* nativeWindowHandle, unsigned width = 800, unsigned height = 600);

		GraphicsDevice(GraphicsDevice&) = delete;
		GraphicsDevice(GraphicsDevice&&) = delete;

		GraphicsDevice& operator=(const GraphicsDevice&) = delete;
		GraphicsDevice& operator=(GraphicsDevice&&) = delete;

		bool EnableVSync;

		Math::Point Resolution() const noexcept override;

		void ResizeBackBuffer(const Math::Point& newResolution) override;
		void ToggleFullScreen() override;

		void SetScreenQuad() override;
		void DrawScreenQuad() override;

		IRenderTarget* GetBackBuffer() override;
		ITexture2D *GetBackBufferTexture() override;
		IDepthStencilBuffer& GetDepthBuffer() override;

		//Graphics::PixelFormat BackBufferFormat() const noexcept;

		~GraphicsDevice() override;
	};
}