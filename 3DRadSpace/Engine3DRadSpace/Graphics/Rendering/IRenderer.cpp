/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/Rendering/IRenderer.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "IRenderer.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;
using namespace Engine3DRadSpace::Graphics::Shaders;

IRenderer::IRenderer(GraphicsDevice* device):
	_device(device)
{
}

void IRenderer::Draw(ModelMeshPart* part)
{
	part->Draw();
}

void IRenderer::Draw(VertexBuffer* vertices, IndexBuffer* indices)
{
	_device->DrawVertexBufferWithindices(vertices, indices);
}
