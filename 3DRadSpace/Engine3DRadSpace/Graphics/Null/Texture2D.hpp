#pragma once
#include "../PixelFormat.hpp"
#include "../../Math/Point.hpp"
#include "../../Content/IAsset.hpp"
#include "../../Math/Color.hpp"
#include "../ITexture2D.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class GraphicsDevice;
	class DepthStencilBuffer;
	/// <summary>
	/// Represents a 2D texture.
	/// <remarks>
	/// </remarks>
	class E3DRSP_GRAPHICS_EXPORT Texture2D : public ITexture2D
	{
	public:
		Texture2D(GraphicsDevice* device, const std::filesystem::path& path);

		explicit Texture2D(GraphicsDevice *device, std::span<Math::Color> colors, unsigned x, unsigned y);

		explicit Texture2D(GraphicsDevice *device, Math::Color* colors, unsigned x, unsigned y);

		explicit Texture2D(GraphicsDevice *device, void* buffer, unsigned x, unsigned y, PixelFormat format = PixelFormat::R32G32B32A32_Float);

		explicit Texture2D(GraphicsDevice *device, const uint8_t* imageBuffer, size_t size);

		explicit Texture2D(GraphicsDevice *device, unsigned x, unsigned y, PixelFormat format = PixelFormat::R32G32B32A32_Float);

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D&&) noexcept = default;

		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&&) noexcept = default;

		void SetColors(Math::Color** colors, unsigned x, unsigned y);

		void SaveToFile(const std::string &path);

		unsigned Width() const noexcept override;
		unsigned Height() const noexcept override;
		Math::Point Size() const noexcept override;

		[[nodiscard]] std::unique_ptr<ITexture2D> CreateStaging() override;

		static Texture2D CreateStaging(Texture2D* texture);
		Texture2D Clone();

		std::pair<void*, size_t> BeginRead(unsigned resourceID = 0);
		void EndRead(unsigned resourceID = 0);

		virtual void* GetHandle() const noexcept override;
		virtual IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		size_t ReadData(void **data) override;
		void SetData(void *data, size_t buffSize) override;
		void EndRead() override;

		void* GetViewHandle() const noexcept override;

		~Texture2D() override = default;
	};
}

