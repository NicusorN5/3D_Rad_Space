#pragma once
#include "PixelFormat.hpp"
#include "../Math/Point.hpp"
#include "../Content/IAsset.hpp"
#include "../Color.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DepthStencilBuffer;
	class DLLEXPORT Texture2D : public Content::IAsset
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

        DXGI_FORMAT _getTextureFormat(PixelFormat format);
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
		Texture2D(GraphicsDevice* device, const std::filesystem::path& path);

		explicit Texture2D(GraphicsDevice *device, std::span<Color> colors, unsigned x, unsigned y);
		explicit Texture2D(GraphicsDevice *device, Color* colors, unsigned x, unsigned y);
		explicit Texture2D(GraphicsDevice *device, void* buffer, unsigned x, unsigned y, PixelFormat format = PixelFormat::R32G32B32A32_Float);
		explicit Texture2D(GraphicsDevice *device, const uint8_t* imageBuffer, size_t size);
		explicit Texture2D(GraphicsDevice *device, unsigned x, unsigned y, PixelFormat format = PixelFormat::R32G32B32A32_Float);

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D&&) noexcept = default;

		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&&) noexcept = default;

		void SetColors(Color** colors, unsigned x, unsigned y);
		void Resize(unsigned newX, unsigned newY);

		void SaveToFile(const std::string &path);

		unsigned Width() const noexcept;
		unsigned Height() const noexcept;
		Math::Point Size() const noexcept;

        static Texture2D CreateStaging(Texture2D* texture);
        Texture2D Clone();

		void* TextureHandle() const noexcept;
		void* ResourceViewHandle() const noexcept;

		virtual ~Texture2D() = default;

		Reflection::UUID GetUUID() const noexcept override;
		const char* FileExtension() const noexcept override;

		friend class Engine3DRadSpace::GraphicsDevice;
		friend class IVertexShader;
		friend class IFragmentShader;
		friend class IHullShader;
		friend class IDomainShader;
		friend class IGeometryShader;
		friend struct Internal::AssetUUIDReader;
		friend class DepthStencilBuffer;
	};
}

