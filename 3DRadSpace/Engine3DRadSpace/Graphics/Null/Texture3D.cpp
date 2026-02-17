#include "Texture3D.hpp"
#include "GraphicsDevice.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

Texture3D::Texture3D() : _device(nullptr)
{ 
}

Texture3D::Texture3D(GraphicsDevice* device, std::span<Texture2D*> textures) :
	_device(nullptr)
{
	(void)textures;
}

Math::UPoint3 Texture3D::Size() const noexcept
{
	return Math::UPoint3{};
}

unsigned Texture3D::Width() const noexcept
{
	return 0;
}
unsigned Texture3D::Height() const noexcept
{
	return 0;
}

unsigned Texture3D::Depth() const noexcept
{
	return 0;
}

void* Texture3D::GetViewHandle() const noexcept
{
	return nullptr;
}

size_t Texture3D::ReadData(size_t subResource, void** data)
{
	(void)subResource;
	(void)data;

	return 0;
}

void Texture3D::SetData(size_t subResource, void* data, size_t buffSize)
{
	(void)subResource;
	(void)data;
	(void)buffSize;
}

void Texture3D::EndRead(size_t subResource)
{
	(void)subResource;
}

void* Texture3D::GetHandle() const noexcept
{
	return nullptr;
}

IGraphicsDevice* Texture3D::GetGraphicsDevice() const noexcept
{
	return _device;
}

[[nodiscard]] std::unique_ptr<ITexture3D> Texture3D::CreateStaging()
{
	return std::make_unique<Texture3D>(std::move(Texture3D()));
}