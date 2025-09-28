#include "DepthStencilBuffer.hpp"

using namespace Engine3DRadSpace
using namespace Engine3DRadSpace::Graphics
using namespace Engine3DRadSpace::Graphics::Null

DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice* device)
{
}

DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice* device, unsigned x, unsigned y)
{
}
void* DepthStencilBuffer::GetViewHandle() const noexcept override
{
	return nullptr;
}
void* DepthStencilBuffer::GetDepthTextureHandle() const noexcept override
{
	return nullptr;
}
Texture2D* DepthStencilBuffer::GetDepthTexture() const noexcept override
{
	return nullptr;
}

Texture2D DepthStencilBuffer::CloneDepthTexture() override
{
	return nullptr;
}

void* DepthStencilBuffer::GetHandle() const noexcept override
{
	return nullptr;
}