#include "FontRenderer.hpp"
#include "../SpriteBatch.hpp"
#include "../../Math/Rectangle.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Fonts;
using namespace Engine3DRadSpace::Math;

FontRenderer::FontRenderer(GraphicsDevice* device) :
	_device(device),
	_shader(std::make_unique<FontShader>(device)),
	_samplerState(std::make_unique<SamplerState>(device)),
	_rasterizer(std::make_unique<RasterizerState>(RasterizerState::CullNone(device)))
{
}

void FontRenderer::Render(Font& font, char chr)
{
	_shader->SetAll();
	_shader->SetTexture(font[chr]);
	_shader->SetSampler(_samplerState.get());
	_shader->SetTintColor(Colors::White);
	_device->SetRasterizerState(_rasterizer.get());
	_device->SetTopology(VertexTopology::TriangleList);

	auto quads = SpriteBatch::_createQuad(RectangleF(0.0f,0.0f,1.0f,1.0f));

	VertexBufferV<VertexPointUV> buff(_device, quads);
	buff.Draw(0);
}
