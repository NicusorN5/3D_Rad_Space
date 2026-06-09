#include "ForwardRenderer.hpp"
#include "../Effect.hpp"
#include "../IGraphicsCommandList.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

ForwardRenderer::ForwardRenderer(IGraphicsDevice* device):
	IRenderer(device)
{
}

void ForwardRenderer::Begin()
{
	if (_beginCalled) return;
	_beginCalled = true;

	_device->ImmediateContext()->SetRenderTargetAndDepth(nullptr, nullptr);
}

void ForwardRenderer::DrawItem(const BatchedDraw& item)
{
	if (item.Material == nullptr || item.Vertices == nullptr || item.Indices == nullptr)
		return;

	if (!item.ForwardConstants.empty())
	{
		item.Material->SetData(
			static_cast<void*>(const_cast<std::byte*>(item.ForwardConstants.data())),
			item.ForwardConstants.size(),
			0
		);
	}

	item.Material->SetAll();

	auto cmd = _device->ImmediateContext();
	cmd->SetTopology(VertexTopology::TriangleList);
	cmd->DrawVertexBufferWithindices(item.Vertices, item.Indices);
}

void ForwardRenderer::End()
{
	_beginCalled = false;
}
