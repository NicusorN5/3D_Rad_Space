#include "DepthStencilBuffer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice* device)
{
}

DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice* device, unsigned x, unsigned y)
{
}

void* DepthStencilBuffer::GetHandle() const noexcept
{
	return nullptr;
}

void* DepthStencilBuffer::GetDepthTextureHandle() const noexcept
{
	return nullptr;
}

ITexture2D* DepthStencilBuffer::GetDepthTexture() const noexcept
{
	return nullptr;
}

std::unique_ptr<ITexture2D> DepthStencilBuffer::CloneDepthTexture()
{
	return nullptr;
}

IGraphicsDevice* DepthStencilBuffer::GetGraphicsDevice() const noexcept
{
	return nullptr;
}