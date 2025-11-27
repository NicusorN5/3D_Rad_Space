#include "RenderTarget.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

RenderTarget::RenderTarget(GraphicsDevice *device, PixelFormat format) :
	Texture2D(device, nullptr, 0, 0, format)
{
	(void)device;
	(void)format;
}

RenderTarget::RenderTarget(GraphicsDevice * device, unsigned x, unsigned y, PixelFormat format) 
	: Texture2D(device, nullptr, x, y, format)
{
	(void)device;
	(void)x;
	(void)y;
	(void)format;
}

void* RenderTarget::RenderTargetHandle() const noexcept
{
	return nullptr;
}

RenderTarget RenderTarget::GetCurrentRenderTarget(GraphicsDevice* device)
{
	(void)device;
	return RenderTarget(nullptr, 0, 0, PixelFormat::Unknown);
}
std::array<RenderTarget*, 8> RenderTarget::GetCurrentRenderTargets(GraphicsDevice* device)
{
	(void)device;
	std::array<RenderTarget*, 8> r{0};
	return r;
}