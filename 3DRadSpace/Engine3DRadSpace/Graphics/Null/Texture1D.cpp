#include "Texture1D.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

Texture1D::Texture1D(GraphicsDevice* device, size_t numElements, PixelFormat format)
{
	(void)device;
	(void)numElements;
	(void)format;
}

Texture1D::Texture1D(GraphicsDevice* device, std::span<Math::Color> colors)
{
	(void)device;
	(void)colors;
}

size_t Texture1D::Length() const noexcept
{
	return 0;
}

void* Texture1D::GetViewHandle() const noexcept
{
	return nullptr;
}

[[nodiscard]] std::unique_ptr<ITexture1D> Texture1D::CreateStaging()
{
	return std::make_unique<Texture1D>(nullptr, 0, PixelFormat::Unknown);
}

size_t Texture1D::ReadData(size_t subresource, void** data)
{
	(void)subresource;
	(void)data;
	return 0;
}

void Texture1D::SetData(size_t subresource, void* data, size_t buffSize)
{
	(void)subresource;
	(void)data;
	(void)buffSize;
}

void Texture1D::EndRead(size_t subresource)
{
	(void)subresource;
}

void* Texture1D::GetHandle() const noexcept
{
	return nullptr;
}
IGraphicsDevice* Texture1D::GetGraphicsDevice() const noexcept
{
	return nullptr;
}