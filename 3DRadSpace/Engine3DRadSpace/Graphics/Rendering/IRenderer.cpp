#include "IRenderer.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;

IRenderer::IRenderer(IGraphicsDevice* device):
	_device(device)
{
}

void IRenderer::Draw(ModelMeshPart* part)
{
	part->Draw();
}

void IRenderer::Draw(IVertexBuffer* vertices, IIndexBuffer* indices)
{
	_device->ImmediateContext()->DrawVertexBufferWithindices(vertices, indices);
}
