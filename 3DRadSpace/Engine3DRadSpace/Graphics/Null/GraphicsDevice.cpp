#include "GraphicsDevice.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;
using namespace Engine3DRadSpace::Math;

GraphicsDevice::GraphicsDevice(void* nativeWindowHandle, unsigned width, unsigned height)
{
	(void)nativeWindowHandle;
	(void)width;
	(void)height;
}

void GraphicsDevice::Clear(const Math::Color& clearColor) override
{
	(void)clearColor;
}

void GraphicsDevice::ClearRenderTarget(IRenderTarget* rt, const Math::Color& clearColor) override
{
	(void)rt;
	(void)clearColor;
}

void GraphicsDevice::ClearDepthBuffer(IDepthStencilBuffer* depth) override
{
	(void)depth;
}

void GraphicsDevice::SetViewport() override
{
}

void GraphicsDevice::SetViewport(const Viewport& viewport) override
{
	(void)viewport;
}

void GraphicsDevice::SetViewports(std::span<Viewport> viewports) override
{
	(void)viewports;
}

Viewport GraphicsDevice::GetViewport() override
{

}

void GraphicsDevice::SetRenderTarget(IRenderTarget* renderTarget) override
{
	(void)renderTarget;
}

void GraphicsDevice::UnbindRenderTargetAndDepth() override
{
}

void GraphicsDevice::UnbindDepthBuffer() override
{
}

void GraphicsDevice::SetRenderTargetAndDepth(IRenderTarget* renderTarget, IDepthStencilBuffer* depthBuffer) override
{
	(void)renderTarget;
	(void)depthBuffer;
}

void GraphicsDevice::SetRenderTargetAndDisableDepth(IRenderTarget* renderTarget) override
{
	(void)renderTarget;
}

void GraphicsDevice::DrawVertexBufferWithindices(IVertexBuffer *vertexBuffer, IIndexBuffer *indexBuffer) override
{
	(void)vertexBuffer;
	(void)indexBuffer;
}
void GraphicsDevice::DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer, unsigned numIndices) override
{
	(void)vertexBuffer;
	(void)indexBuffer;
	(void)numIndices;
}

void GraphicsDevice::SetShader(IShader* shader) override
{
	(void)shader;
}

void GraphicsDevice::SetRasterizerState(const IRasterizerState* state) override
{
	(void)state;
}

IRasterizerState* GraphicsDevice::GetRasterizerState() override
{

}

void GraphicsDevice::SetDepthStencilBuffer(IDepthStencilBuffer* depthBuffer) override
{
	(void)depthBuffer;
}

void GraphicsDevice::SetDepthStencilState(IDepthStencilState* depthState, unsigned ref) override
{
	(void)depthState;
	(void)ref;
}

void GraphicsDevice::SetBlendState(IBlendState* blendState, const Math::Color& blendFactor, unsigned sampleMask) override
{
	(void)blendState;
	(void)blendFactor;
	(void)sampleMask;
}

void GraphicsDevice::SetTopology(VertexTopology topology) override
{
	(void)topology;
}

void GraphicsDevice::DrawAuto() override
{
}

void GraphicsDevice::Present() override
{
}

void GraphicsDevice::SaveBackBufferToFile(const std::filesystem::path& path) override
{
	(void)path;
}

Math::Point GraphicsDevice::Resolution() const noexcept override
{
	return Math::Point(0, 0);
}

void GraphicsDevice::ResizeBackBuffer(const Math::Point& newResolution) override
{
	(void)newResolution;
}
void GraphicsDevice::ToggleFullScreen() override
{
}

void GraphicsDevice::SetScreenQuad() override
{
}

void GraphicsDevice::DrawScreenQuad() override
{
}

IRenderTarget* GraphicsDevice::GetBackBuffer() override
{
}

ITexture2D* GraphicsDevice::GetBackBufferTexture() override
{
}

IDepthStencilBuffer& GraphicsDevice::GetDepthBuffer() override
{
}

//Graphics::PixelFormat BackBufferFormat() const noexcept;
