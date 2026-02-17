#include "ForwardRenderer.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;

ForwardRenderer::ForwardRenderer(IGraphicsDevice* device, Effect* pipeline):
	IRenderer(device)
{
}

void ForwardRenderer::Begin()
{
	if (_beginCalled) return;
	_beginCalled = true;

	_device->ImmediateContext()->SetRenderTargetAndDepth(nullptr, nullptr);
}

void ForwardRenderer::End()
{
	_beginCalled = false;
}
