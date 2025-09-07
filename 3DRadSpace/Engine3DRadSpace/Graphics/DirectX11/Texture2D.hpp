#pragma once
#include "../PixelFormat.hpp"
#include "../../Math/Point.hpp"
#include "../../Content/IAsset.hpp"
#include "../../Math/Color.hpp"
#include "../ITexture2D.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class DepthStencilBuffer;
	/// <summary>
	/// Represents a 2D texture.
	/// <remarks>
	/// </remarks>
	class E3DRSP_GRAPHICS_EXPORT Texture2D : public ITexture2D
	{
		unsigned _width;
		unsigned _height;

		void _debugInfoTX2D();
		void _debugInfoRT();
        explicit Texture2D(GraphicsDevice* device, Microsoft::WRL::ComPtr<ID3D11Texture2D>&& texture, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>&& resource);
        explicit Texture2D(GraphicsDevice* device, std::monostate dummy, Microsoft::WRL::ComPtr<ID3D11Texture2D>&& texture);
	protected:
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _resourceView;
		GraphicsDevice *_device;
		PixelFormat _format;

        DXGI_FORMAT _getTextureFormat(PixelFormat format);
		PixelFormat _getTextureFormatFromDX(DXGI_FORMAT format);
#endif
		void _retrieveSize();

		explicit Texture2D(GraphicsDevice *device, unsigned x, unsigned y, bool bindRenderTarget, PixelFormat format = PixelFormat::R32G32B32A32_Float);
		/// <summary>
		/// Used by RenderTarget.
		/// </summary>
		/// <param name="device"></param>
		/// <param name="dummy">Hack. Used because C++ converts const char* to bool by default over std::filesystem::path.</param>
		/// <param name="bindRenderTarget">Bind render target creation flag</param>
		/// <param name="format">Texture format.</param>
		explicit Texture2D(GraphicsDevice *device, std::monostate dummy, bool bindRenderTarget, PixelFormat format = PixelFormat::R32G32B32A32_Float);
		explicit Texture2D(Internal::AssetUUIDReader);
	public:
		/// <summary>
		/// Loads a texture from a file.
		/// </summary>
		/// <param name="device">Device context</param>
		/// <param name="path">Image file</param>
		Texture2D(GraphicsDevice* device, const std::filesystem::path& path);

		/// <summary>
		/// Creates a texture from a span of Colors.
		/// </summary>
		/// <param name="device">Device context.</param>
		/// <param name="colors">Color array. Size must be x * y.</param>
		/// <param name="x">Width of the texture</param>
		/// <param name="y">Height</param>
		explicit Texture2D(GraphicsDevice *device, std::span<Math::Color> colors, unsigned x, unsigned y);
		/// <summary>
		/// Creates a texture from a Color array.
		/// <param name="device">Device context.</param>
		/// <param name="colors">Color array. Size must be x * y.</param>
		/// <pram name="x">Width of the texture.</param>
		/// <param name="y">Height of the texture.</param>
		explicit Texture2D(GraphicsDevice *device, Math::Color* colors, unsigned x, unsigned y);
		/// <summary>
		/// Creates a texture from a buffer with a specified pixel format.
		/// </summary>
		/// <param name="device">Device context.</param>
		/// <param name="colors">Color array. Size must be x * y.</param>
		/// <pram name="x">Width of the texture.</param>
		/// <param name="y">Height of the texture.</param>
		/// <param name="format">Pixel format.</param>
		explicit Texture2D(GraphicsDevice *device, void* buffer, unsigned x, unsigned y, PixelFormat format = PixelFormat::R32G32B32A32_Float);
		/// <summary>
		/// Creates a texture from an image buffer.
		/// </summary>
		/// <param name="device">Device context.</param>
		/// <param name="imageBuffer">Must be an image.</param>
		/// <param name="size">Size of the buffer.</param>
		/// <remarks>
		/// This calls CreateWICTextureFromMemory.
		/// </remarks>
		explicit Texture2D(GraphicsDevice *device, const uint8_t* imageBuffer, size_t size);
		/// <summary>
		/// Creates a texture with specified width, height and format, but unspecified initial data.
		/// </summary>
		/// <param name="device">Device context.</param>
		/// <param name="x">Width</param>
		/// <param name="y">Height</param>
		/// <param name="format">Pixel format</param>
		explicit Texture2D(GraphicsDevice *device, unsigned x, unsigned y, PixelFormat format = PixelFormat::R32G32B32A32_Float);

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D&&) noexcept = default;

		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&&) noexcept = default;

		void SetColors(Math::Color** colors, unsigned x, unsigned y);
		/// <summary>
		/// Resizes the texture using nearest neighbor interpolation.
		/// </summary>
		/// <param name="newX">New width</param>
		/// <param name="newY">New height</param>
		void Resize(unsigned newX, unsigned newY);

		void SaveToFile(const std::string &path);

		unsigned Width() const noexcept override;
		unsigned Height() const noexcept override;
		Math::Point Size() const noexcept override;

        static Texture2D CreateStaging(Texture2D* texture);
        Texture2D Clone();

		std::pair<void*,size_t> BeginRead(unsigned resourceID = 0);
		void EndRead(unsigned resourceID = 0);

		static void Copy(Texture2D* destination, Texture2D* source);

		void* TextureHandle() const noexcept;
		void* ResourceViewHandle() const noexcept;

		virtual ~Texture2D() = default;

		friend class GraphicsDevice;
		friend class IVertexShader;
		friend class IFragmentShader;
		friend class IHullShader;
		friend class IDomainShader;
		friend class IGeometryShader;
		friend struct Internal::AssetUUIDReader;
		friend class DepthStencilBuffer;
	};
}

