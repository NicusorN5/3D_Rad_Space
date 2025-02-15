/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/Primitives/Lines.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "Lines.hpp"
#include "../../Content/ShaderManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

Lines::Lines(GraphicsDevice* device, std::span<VertexPositionColor> points) :
	IPrimitive(device)
{
	_vertices = std::make_unique<VertexBufferV<VertexPositionColor>>(device, points);
	_lineRasterizer = std::make_unique<RasterizerState>(device, RasterizerFillMode::Solid, RasterizerCullMode::None);
}

VertexBufferV<VertexPositionColor>* Lines::GetVertexBuffer() const noexcept
{
	return _vertices.get();
}

RasterizerState* Lines::GetLineRasterizer() const noexcept
{
	return _lineRasterizer.get();
}

void Lines::Draw3D()
{
	//TODO: Remove low level call, provide method to get old raster state and swap later.
#ifdef USING_DX11
	_device->_context->RSGetState(_oldRasterizerState.GetAddressOf());
#endif
	_shader->SetAll();
	_shader->SetTransformation(_mvp());

	_device->SetRasterizerState(_lineRasterizer.get());
	_device->SetTopology(VertexTopology::LineList);
	_vertices->Draw();
#ifdef USING_DX11
	_device->_context->RSSetState(_oldRasterizerState.Get());
#endif
}
