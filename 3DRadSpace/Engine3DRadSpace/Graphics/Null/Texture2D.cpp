#include "Texture2D.hpp"
#include "GraphicsDevice.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

Texture2D::Texture2D(GraphicsDevice* device, const std::filesystem::path& path)
{
	(void)device;
	(void)path;
}

Texture2D::Texture2D(GraphicsDevice *device, std::span<Math::Color> colors, size_t x, size_t y)
{
	(void)device;
	(void)colors;
	(void)x;
	(void)y;
}

Texture2D::Texture2D(GraphicsDevice *device, void* buffer, size_t x, size_t y, PixelFormat format, BufferUsage usage)
{
	(void)device;
	(void)buffer;
	(void)x;
	(void)y;
	(void)format;
}

Texture2D::Texture2D(GraphicsDevice *device, const uint8_t* imageBuffer, size_t size)
{
	(void)device;
	(void)imageBuffer;
	(void)size;
}

void Texture2D::SetColors(Math::Color** colors, unsigned x, unsigned y)
{
	(void)colors;
	(void)x;
	(void)y;
}

void Texture2D::SaveToFile(const std::filesystem::path& path)
{
	(void)path;
}

unsigned Texture2D::Width() const noexcept
{
	return 0;
}

unsigned Texture2D::Height() const noexcept
{
	return 0;
}

Math::Point Texture2D::Size() const noexcept
{
	return Math::Point(0, 0);
}

[[nodiscard]] std::unique_ptr<ITexture2D> Texture2D::CreateStaging()
{
	return std::unique_ptr<ITexture2D>();
}

Texture2D Texture2D::Clone()
{
	return Texture2D(nullptr, "");
}

void* Texture2D::GetHandle() const noexcept
{
	return nullptr;
}
IGraphicsDevice* Texture2D::GetGraphicsDevice() const noexcept
{
	return nullptr;
}

size_t Texture2D::ReadData(size_t subResource, void **data)
{
	(void)subResource;

	if(data != nullptr) *data = nullptr;
	return 0;
}

void Texture2D::SetData(size_t subResource, void *data, size_t buffSize)
{
	(void)subResource;
	(void)data;
	(void)buffSize;
}

void Texture2D::EndRead(size_t subResource)
{
	(void)subResource;
}

void* Texture2D::GetViewHandle() const noexcept
{
	return nullptr;
}