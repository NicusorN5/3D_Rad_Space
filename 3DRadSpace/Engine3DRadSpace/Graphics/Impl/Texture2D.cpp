#include "Texture2D.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

Texture2D::Texture2D(GraphicsDevice* device, const std::filesystem::path& path)
{
	(void)device;
	(void)path;
}

Texture2D::Texture2D(GraphicsDevice *device, std::span<Math::Color> colors, unsigned x, unsigned y)
{
	(void)device;
	(void)colors;
	(void)x;
	(void)y;
}

Texture2D::Texture2D(GraphicsDevice *device, Math::Color* colors, unsigned x, unsigned y)
{
	(void)device;
	(void)colors;
	(void)x;
	(void)y;
}

Texture2D::Texture2D(GraphicsDevice *device, void* buffer, unsigned x, unsigned y, PixelFormat format)
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

Texture2D::Texture2D(GraphicsDevice *device, unsigned x, unsigned y, PixelFormat format)
{
	(void)device;
	(void)x;
	(void)y;
	(void)format;
}

void Texture2D::SetColors(Math::Color** colors, unsigned x, unsigned y)
{
	(void)colors;
	(void)x;
	(void)y;
}

void Texture2D::Resize(unsigned newX, unsigned newY)
{
	(void)newX;
	(void)newY;
}

void Texture2D::SaveToFile(const std::string &path)
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

Texture2D Texture2D::CreateStaging(Texture2D* texture)
{
	(void)texture;
	return Texture2D(nullptr, "");
}
Texture2D Texture2D::Clone()
{
	return Texture2D(nullptr, "");
}

std::pair<void*, size_t> Texture2D::BeginRead(unsigned resourceID)
{
	(void)resourceID;
	return std::make_pair<void*, size_t>(nullptr, 0);
}

void Texture2D::EndRead(unsigned resourceID)
{
	(void)resourceID;
}

void* Texture2D::GetHandle() const noexcept
{
	return nullptr;
}
IGraphicsDevice* Texture2D::GetGraphicsDevice() const noexcept
{
	return nullptr;
}

size_t Texture2D::ReadData(void **data)
{
	if(data != nullptr) *data = nullptr;
	return 0;
}

void Texture2D::SetData(void *data, size_t buffSize)
{
	(void)data;
	(void)buffSize;
}

void Texture2D::EndRead()
{

}

void Texture2D::Copy(Texture2D* destination, Texture2D* source)
{
	(void)destination;
	(void)source;
}

void* Texture2D::TextureHandle() const noexcept
{
	return nullptr;
}
void* Texture2D::ResourceViewHandle() const noexcept
{
	return nullptr;
}