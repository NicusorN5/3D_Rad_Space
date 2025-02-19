#include "LineStrip.hpp"
#include "../../Content/ShaderManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

void LineStrip::_swapRasterizer()
{
//TODO: Remove low level call, provide method to get old raster state
#ifdef USING_DX11
	_device->_context->RSGetState(_oldRasterizerState.GetAddressOf());
#endif
	_device->SetRasterizerState(_lineRasterizer.get());
}

void LineStrip::_restoreRasterizer()
{
#ifdef USING_DX11
	_device->_context->RSSetState(_oldRasterizerState.Get());
#endif
}

LineStrip::LineStrip(GraphicsDevice* device, std::span<VertexPositionColor> points) :
	IPrimitive(device)
{
	_vertices = std::make_unique<VertexBufferV<VertexPositionColor>>(device, points);
	_lineRasterizer = std::make_unique<RasterizerState>(device, RasterizerFillMode::Solid, RasterizerCullMode::None);
}

VertexBufferV<VertexPositionColor>* LineStrip::GetVertexBuffer() const noexcept
{
	return _vertices.get();
}

RasterizerState* LineStrip::GetLineRasterizer() const noexcept
{
	return _lineRasterizer.get();
}

void LineStrip::Draw3D()
{
	_swapRasterizer();
	_shader->SetAll();
	_shader->SetTransformation(_mvp());

	_device->SetRasterizerState(_lineRasterizer.get());
	_device->SetTopology(VertexTopology::LineStrip);
	_vertices->Draw();
	_restoreRasterizer();
}
