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

void GraphicsDevice::ClearRenderTarget(RenderTarget* rt, const Math::Color& clearColor) override
{
	(void)rt;
	(void)clearColor;
}

void GraphicsDevice::ClearDepthBuffer(DepthStencilBuffer* depth) override
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

void GraphicsDevice::SetRenderTarget(RenderTarget* renderTarget) override
{
	(void)renderTarget;
}

void GraphicsDevice::UnbindRenderTargetAndDepth() override
{
}

void GraphicsDevice::UnbindDepthBuffer() override
{
}

void GraphicsDevice::SetRenderTargetAndDepth(RenderTarget* renderTarget, DepthStencilBuffer* depthBuffer) override
{
	(void)renderTarget;
	(void)depthBuffer;
}

void GraphicsDevice::SetRenderTargetAndDisableDepth(RenderTarget* renderTarget) override
{
	(void)renderTarget;
}

void GraphicsDevice::DrawVertexBufferWithindices(VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer) override
{
	(void)vertexBuffer;
	(void)indexBuffer;
}
void GraphicsDevice::DrawVertexBufferWithindices(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, unsigned numIndices) override
{
	(void)vertexBuffer;
	(void)indexBuffer;
	(void)numIndices;
}

void GraphicsDevice::SetShader(IShader* shader) override
{
	(void)shader;
}

void GraphicsDevice::SetRasterizerState(const RasterizerState* state) override
{
	(void)state;
}

RasterizerState GraphicsDevice::GetRasterizerState() override
{

}

void GraphicsDevice::SetDepthStencilBuffer(DepthStencilBuffer* depthBuffer) override
{
	(void)depthBuffer;
}

void GraphicsDevice::SetDepthStencilState(DepthStencilState* depthState, unsigned ref) override
{
	(void)depthState;
	(void)ref;
}

void GraphicsDevice::SetBlendState(BlendState* blendState, const Math::Color& blendFactor, unsigned sampleMask) override
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

RenderTarget* GraphicsDevice::GetBackBuffer() override
{
}

Texture2D* GraphicsDevice::GetBackBufferTexture() override
{
}

DepthStencilBuffer& GraphicsDevice::GetDepthBuffer() override
{
}

//Graphics::PixelFormat BackBufferFormat() const noexcept;
