#include "GraphicsCommandList.hpp"
#include "RasterizerState.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

GraphicsCommandList::GraphicsCommandList(GraphicsDevice* device)
{
	(void)device;
}

void GraphicsCommandList::Clear(const Math::Color& clearColor)
{
	(void)clearColor;
}

void GraphicsCommandList::ClearRenderTarget(IRenderTarget* rt, const Math::Color& clearColor)
{
	(void)rt;
	(void)clearColor;
}

void GraphicsCommandList::ClearDepthBuffer(IDepthStencilBuffer* depth)
{
	(void)depth;
}

void GraphicsCommandList::SetViewport()
{
}

void GraphicsCommandList::SetViewport(const Viewport& viewport)
{
	(void)viewport;
}

void GraphicsCommandList::SetViewports(std::span<Viewport> viewports)
{
	(void)viewports;
}

Viewport GraphicsCommandList::GetViewport()
{

}

void GraphicsCommandList::SetRenderTarget(IRenderTarget* renderTarget)
{
	(void)renderTarget;
}

void GraphicsCommandList::UnbindRenderTargetAndDepth()
{
}

void GraphicsCommandList::UnbindDepthBuffer()
{
}

void GraphicsCommandList::SetRenderTargetAndDepth(IRenderTarget* renderTarget, IDepthStencilBuffer* depthBuffer)
{
	(void)renderTarget;
	(void)depthBuffer;
}

void GraphicsCommandList::SetRenderTargetAndDisableDepth(IRenderTarget* renderTarget)
{
	(void)renderTarget;
}

void GraphicsCommandList::DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer)
{
	(void)vertexBuffer;
	(void)indexBuffer;
}
void GraphicsCommandList::DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer, unsigned numIndices)
{
	(void)vertexBuffer;
	(void)indexBuffer;
	(void)numIndices;
}

void GraphicsCommandList::SetShader(IShader* shader)
{
	(void)shader;
}

void GraphicsCommandList::SetRasterizerState(const IRasterizerState* state)
{
	(void)state;
}

std::unique_ptr<IRasterizerState> GraphicsCommandList::GetRasterizerState()
{
	return std::make_unique<RasterizerState>(this);
}

void GraphicsCommandList::SetDepthStencilBuffer(IDepthStencilBuffer* depthBuffer)
{
	(void)depthBuffer;
}

void GraphicsCommandList::SetDepthStencilState(IDepthStencilState* depthState, unsigned ref)
{
	(void)depthState;
	(void)ref;
}

void GraphicsCommandList::SetBlendState(IBlendState* blendState, const Math::Color& blendFactor, unsigned sampleMask)
{
	(void)blendState;
	(void)blendFactor;
	(void)sampleMask;
}

void GraphicsCommandList::SetTopology(VertexTopology topology)
{
	(void)topology;
}

void GraphicsCommandList::DrawAuto()
{
}

void GraphicsCommandList::Present()
{
}

void GraphicsCommandList::SaveBackBufferToFile(const std::filesystem::path& path)
{
	(void)path;
}

void GraphicsCommandList::ResizeBackBuffer(const Math::Point& newResolution)
{
	(void)newResolution;
}
void GraphicsCommandList::ToggleFullScreen()
{
}