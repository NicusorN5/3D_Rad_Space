#include "RenderTarget.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

RenderTarget::RenderTarget(IGraphicsDevice *device, PixelFormat format)
{
	(void)device;
	(void)format;
}

RenderTarget::RenderTarget(IGraphicsDevice * device, unsigned x, unsigned y, PixelFormat format)
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

RenderTarget RenderTarget::GetCurrentRenderTarget(IGraphicsDevice* device)
{
	(void)device;
	return RenderTarget(nullptr, 0, 0, PixelFormat::Unknown);
}
std::array<RenderTarget*, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> RenderTarget::GetCurrentRenderTargets(IGraphicsDevice* device)
{
	(void)device;
	std::array<RenderTarget*, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> r{0};
	return r;
}