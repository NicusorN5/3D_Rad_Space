#include "SpriteBatch.hpp"
#include "../Math/Matrix3x3.hpp"
#include "../Math/Math.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

constexpr Math::RectangleF _fullDefaultUV(0.0f, 0.0f, 1.0f, 1.0f);

std::array<VertexPointUVColor,4> SpriteBatch::_createQuad(
	const RectangleF &r, 
	bool flipU,
	bool flipV, 
	const Color &tintColor,
	const RectangleF &uvRect
)
{
/*
	B -- C
	|  / |
	| /  |
	A -- D

	(winding order is clockwise.)
	A -> B -> C
	C -> D -> A
*/
	Vector2 a = r.BottomLeft();
	Vector2 b = r.TopLeft();
	Vector2 c = r.TopRight();
	Vector2 d = r.BottomRight();

	return _createQuad(a, b, c, d, flipU, flipV, tintColor, uvRect);
}

std::array<VertexPointUVColor, 4> SpriteBatch::_createQuad(const Math::Vector2& a, const Math::Vector2& b, const Math::Vector2& c, const Math::Vector2& d, bool flipU, bool flipV,const Color &tintColor, const Math::RectangleF &uvRect)
{
	Vector2 uv_a = uvRect.BottomLeft();
	Vector2 uv_b = uvRect.TopLeft();
	Vector2 uv_c = uvRect.TopRight();
	Vector2 uv_d = uvRect.BottomRight();

	if (flipU)
	{
		auto flipX = [](Vector2& uv)
		{
			uv.X = 1 - uv.X;
		};

		flipX(uv_a);
		flipX(uv_b);
		flipX(uv_c);
		flipX(uv_d);
	}

	if (flipV)
	{
		auto flipY = [](Vector2& uv)
		{
			uv.Y = 1 - uv.Y;
		};

		flipY(uv_a);
		flipY(uv_b);
		flipY(uv_c);
		flipY(uv_d);
	}

	std::array quad =
	{
		VertexPointUVColor{Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(a), uv_a, tintColor},
		VertexPointUVColor{Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(b), uv_b, tintColor},
		VertexPointUVColor{Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(c), uv_c, tintColor},
		VertexPointUVColor{Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(d), uv_d, tintColor},
	};

	return quad;
}

std::array<unsigned, 6> SpriteBatch::_createIndexQuad(unsigned offset)
{
	return std::array<unsigned, 6>{
		offset, // A
		offset + 1, // B
		offset + 2, // C

		offset + 2, //C
		offset + 3, //D
		offset //A
	};
}

void SpriteBatch::_prepareGraphicsDevice()
{
	_spriteShader->SetBasic();
	_spriteShader->SetSamplerState(_samplerState.get());

#ifdef USING_DX11
	_device->_context->RSGetState(&_oldRasterizerState);
	_device->_context->OMGetBlendState(&_oldBlendState, _oldBlendFactor, &_oldSampleMask);
	_device->_context->OMGetDepthStencilState(&_oldStencilState, &_oldStencilRef);
#endif
	_device->SetRasterizerState(_rasterizerState.get());
	_device->SetTopology(VertexTopology::TriangleList);
	_device->SetBlendState(_blendState.get());
}

void SpriteBatch::_drawEntry(const spriteBatchEntry &entry)
{
	auto [min, max] = entry.coords;

	auto center = (max + min) / 2.0f;

	auto rotation = Matrix3x3::CreateRotation2D(entry.rotation);
	auto tr = Matrix3x3::CreateTranslation(center);

	Vector2 a(min.X, max.Y); //bottom left
	Vector2 b(min.X, min.Y); //top left
	Vector2 c(max.X, min.Y); //top right
	Vector2 d(max.X, max.Y); //bottom right

	a -= center;
	b -= center;
	c -= center;
	d -= center;

	a.Transform(rotation).Transform(tr);
	b.Transform(rotation).Transform(tr);
	c.Transform(rotation).Transform(tr);
	d.Transform(rotation).Transform(tr);

	auto quad = _createQuad( a, b, c, d, entry.flipU, entry.flipV, entry.tintColor, entry.uvSource);
	_vertexBuffer->SetData(quad);

	auto indices = _createIndexQuad(0);
	_indexBuffer->SetData(indices);

	_prepareGraphicsDevice();

	_spriteShader->SetTexture(_textures[entry.textureID]);

	_device->DrawVertexBufferWithindices(_vertexBuffer.get(), _indexBuffer.get());
	_restoreGraphicsDevice();
}

void SpriteBatch::_drawAllEntries_SortByTexture()
{
	unsigned lastID = 1;

	std::vector<VertexPointUVColor> currentVertices;
	std::vector<unsigned> currentIndices;
	_prepareGraphicsDevice();

	auto draw = [&]()
	{
		_vertexBuffer->SetData(currentVertices);
		_indexBuffer->SetData(currentIndices);
		_device->DrawVertexBufferWithindices(_vertexBuffer.get(), _indexBuffer.get());
		_device->DrawVertexBuffer(_vertexBuffer.get());
	};

	unsigned i = 0;
	for(auto &entry : _entries)
	{
		if(entry.textureID == lastID)
		{
			auto& [min, max] = entry.coords;
			auto quad = _createQuad(
				Math::RectangleF(min,max),
				entry.flipU, 
				entry.flipV,
				entry.tintColor,
				entry.uvSource
			);
			currentVertices.insert(currentVertices.end(), quad.begin(), quad.end());

			auto indices = _createIndexQuad(i);
			currentIndices.insert(currentIndices.end(), indices.begin(), indices.end());
			i += 4; //4 vertices per quad
		}
		else
		{
			//Resize vertex and index GPU buffers when switching texture
			if (currentVertices.size() > _capacity * 4) //if capacity is exceeded, reallocate:
			{
				_capacity *= 2; //growth factor

				_vertexBuffer = std::make_unique<VertexBufferV<VertexPointUVColor>>(_device, nullptr, _capacity * 4);
				_indexBuffer = std::make_unique<IndexBuffer>(_device, nullptr, _capacity * 6);
			}

			lastID = entry.textureID;
			_spriteShader->SetTexture(_textures[entry.textureID]);
			draw();

			currentVertices.clear();
		}
	}

	_spriteShader->SetTexture(_textures[lastID]);
	draw();

	_restoreGraphicsDevice();
}

void SpriteBatch::_drawAllEntries()
{
	_prepareGraphicsDevice();

	for(auto& entry : _entries)
	{
		_drawEntry(entry);
	}
	_restoreGraphicsDevice();
}

void SpriteBatch::_restoreGraphicsDevice()
{
#ifdef USING_DX11
	_device->_context->RSSetState(_oldRasterizerState.Get());
	_device->_context->OMSetBlendState(_oldBlendState.Get(), _oldBlendFactor, _oldSampleMask);
	_device->_context->OMSetDepthStencilState(_oldStencilState.Get(), _oldStencilRef);
#endif
}

SpriteBatch::SpriteBatch(GraphicsDevice *device) :
	_device(device),
	_sortingMode(SpriteBatchSortMode::Immediate),
	_state(Immediate),
	_oldBlendFactor{},
	_oldSampleMask(0),
	_oldStencilRef(0)
{
	_spriteShader = std::make_unique<SpriteShader>(device);
	// 256 quads: 1024 vertices and 1536 indices
	_vertexBuffer = std::make_unique<VertexBufferV<VertexPointUVColor>>(device, nullptr, _capacity * 4);
	_indexBuffer = std::make_unique<IndexBuffer>(device, nullptr, _capacity * 6);

	_rasterizerState = std::make_unique<RasterizerState>(device, RasterizerFillMode::Solid, RasterizerCullMode::CullBack);
	_samplerState = std::make_unique<SamplerState>(SamplerState::PointWrap(device));
	_depthBufferState = std::make_unique<DepthStencilState>(DepthStencilState::DepthNone(device));
	_blendState = std::make_unique<BlendState>(BlendState::AlphaBlend(device));

	_textures.push_back(nullptr);
}

void SpriteBatch::Begin(SpriteBatchSortMode sortingMode)
{
	if(sortingMode == SpriteBatchSortMode::Immediate)
	{
		_state = Immediate;
	}
	else
	{
		if(_state == EndCalled || _state == Immediate)
		{
			_state = BeginCalled;
		}
		else throw std::logic_error("Begin() was called when the sprite batch was waiting for entries.");
	}

	_sortingMode = sortingMode;
}

void SpriteBatch::Begin(SpriteBatchSortMode sortingMode, SamplerState &&samplerState)
{
	_samplerState = std::make_unique<SamplerState>(std::move(samplerState));
	Begin(sortingMode);
}

void SpriteBatch::DrawNormalized(Texture2D* texture, const Math::RectangleF& coords, const Math::RectangleF& source, Color tintColor, float rotation, FlipMode flipMode, float depth)
{
	if (texture == nullptr) return;

	Vector2 min = coords.TopLeft();
	Vector2 max = coords.BottomRight();

	if (_state == Immediate)
	{
		_textures[0] = texture;
		spriteBatchEntry tempEntry
		{
			.textureID = 0u,
			.coords = std::make_pair(min, max),
			.uvSource = source,
			.tintColor = tintColor,
			.flipU = static_cast<bool>(FlipMode::FlipHorizontally & flipMode),
			.flipV = static_cast<bool>(FlipMode::FlipVertically & flipMode),
			.rotation = rotation,
			.depth = depth,
			.sortingMode = SpriteBatchSortMode::Immediate
		};

		_drawEntry(tempEntry);
	}
	
	if (_state == BeginCalled)
	{
		bool textureExists = false;
		unsigned int index = 0;

		//find texture id:
		for (int i = 0; i < _textures.size(); ++i)
		{
			if (_textures[i] == texture)
			{
				textureExists = true;
				index = i;
				break;
			}
		}

		//add new texture handle if it doesn't exist:
		if (!textureExists)
		{
			_textures.push_back(texture);
			index = _textures.size() - 1;
		}

		_entries.insert(
			spriteBatchEntry
			{
				.textureID = index,
				.coords = std::make_pair(min, max),
				.uvSource = source,
				.tintColor = tintColor,
				.flipU = static_cast<bool>(FlipMode::FlipHorizontally & flipMode),
				.flipV = static_cast<bool>(FlipMode::FlipVertically & flipMode),
				.rotation = rotation,
				.depth = depth,
				.sortingMode = SpriteBatchSortMode::Immediate
			}
		);
	}
	if (_state == EndCalled) throw std::logic_error("Cannot draw textures when End() was called.");
}

void SpriteBatch::DrawNormalized(Texture2D* texture, const Math::RectangleF& coords, const Math::Rectangle source, Color tintColor, float rotation, FlipMode flipMode, float depth)
{
	DrawNormalized(texture, coords, _fullDefaultUV, tintColor, rotation, flipMode, depth);
}

void SpriteBatch::Draw(Texture2D* texture, const Math::Rectangle& coords, const Math::Rectangle& source, Color tintColor, float rotation, FlipMode flipMode, float depth)
{
	if (texture == nullptr) return;

	auto screenSize = _device->Resolution();
	RectangleF nCoords(
		static_cast<float>(coords.X) / static_cast<float>(screenSize.X),
		static_cast<float>(coords.Y) / static_cast<float>(screenSize.Y),
		static_cast<float>(coords.Width) / static_cast<float>(screenSize.X),
		static_cast<float>(coords.Height) / static_cast<float>(screenSize.Y)
	);

	auto textureSize = texture->Size();
	RectangleF nSource(
		static_cast<float>(source.X) / static_cast<float>(textureSize.X),
		static_cast<float>(source.Y) / static_cast<float>(textureSize.Y),
		static_cast<float>(source.Width) / static_cast<float>(textureSize.X),
		static_cast<float>(source.Height) / static_cast<float>(textureSize.Y)
	);

	DrawNormalized(texture, nCoords, nSource, tintColor, rotation, flipMode, depth);
}

void SpriteBatch::Draw(Texture2D* texture, const Math::Rectangle& coords, Color tintColor, float rotation, FlipMode flipMode, float depth)
{
	auto screenSize = _device->Resolution();
	RectangleF nCoords(
		static_cast<float>(coords.X) / static_cast<float>(screenSize.X),
		static_cast<float>(coords.Y) / static_cast<float>(screenSize.Y),
		static_cast<float>(coords.Width) / static_cast<float>(screenSize.X),
		static_cast<float>(coords.Height) / static_cast<float>(screenSize.Y)
	);

	DrawNormalized(texture, nCoords, _fullDefaultUV, tintColor, rotation, flipMode, depth);
}

void SpriteBatch::DrawString(Font* font, const std::string& text, const Vector2& pos, float size, Color tintColor, float rotation, FlipMode flipMode, float depth)
{
	if (font == nullptr) return;

	auto oldState = _state;
	auto oldSortMode = _sortingMode;
	auto screenSize = _device->Resolution();

	//accLen = 0 at i = 0.
	//accLen increases with the advance of the current letter per iteration.
	int x = static_cast<int>(pos.X * screenSize.X);
	int y = static_cast<int>(pos.Y * screenSize.Y);

	End();
	Begin(SpriteBatchSortMode::SortedByTexture); //<-- TODO: MUST FIX!
	//Begin(SpriteBatchSortMode::Immediate);

	for (auto&& c : text)
	{
		if (!font->GetCharGlyph(c).has_value()) continue;

		auto glyph = font->GetCharGlyph(c).value();

		Math::Rectangle rcChar;
		// https://learnopengl.com/In-Practice/Text-Rendering
		rcChar.X = x + glyph.Bearing.X * size;
		rcChar.Y = y - (glyph.Bearing.Y * size);
		rcChar.Width = glyph.Size.X * size;
		rcChar.Height = glyph.Size.Y * size;

		auto src = font->GetCharSourceRectangle(c).value();

		Draw(font->GetTexture(), rcChar, src, tintColor, rotation, flipMode, depth);

		x += glyph.Advance >> 6;
	}

	End();
	_state = oldState;
	_sortingMode = oldSortMode;
}

void SpriteBatch::DrawString(Font* font, const std::string& text, const Math::Point& pos, float size, Color tintColor, float rotation, FlipMode flipMode, float depth)
{
	auto screenSize = _device->Resolution();
	Vector2 p(
		static_cast<float>(pos.X) / static_cast<float>(screenSize.X),
		static_cast<float>(pos.Y) / static_cast<float>(screenSize.Y)
	);

	DrawString(font, text, p, size, tintColor, rotation, flipMode, depth);
}

void SpriteBatch::End()
{
	if(_sortingMode == SpriteBatchSortMode::Immediate) return;

	if(_state == BeginCalled)
	{
		//draw all entries
		if(_sortingMode == SpriteBatchSortMode::SortedByTexture)
		{
			_drawAllEntries_SortByTexture();
		}
		else _drawAllEntries();

		_state = EndCalled;
		_textures.clear();
		_textures.push_back(nullptr);

		_entries.clear();
	}
}

bool SpriteBatch::spriteBatchEntry::operator>(const spriteBatchEntry &b) const
{
	switch(sortingMode)
	{
		case SpriteBatchSortMode::Immediate:
		case SpriteBatchSortMode::SortedByTexture:
			return textureID > b.textureID;
		case SpriteBatchSortMode::SortedByDepth_FrontToBack:
			return depth > b.depth;
		default:
			return depth < b.depth;
	}
}

bool SpriteBatch::spriteBatchEntry::operator<(const spriteBatchEntry &b) const
{
	switch(sortingMode)
	{
		case SpriteBatchSortMode::Immediate:
		case SpriteBatchSortMode::SortedByTexture:
			return textureID < b.textureID;
		case SpriteBatchSortMode::SortedByDepth_FrontToBack:
			return depth < b.depth;
		default:
			return depth > b.depth;
	}
}

bool SpriteBatch::spriteBatchEntry::operator==(const spriteBatchEntry &b) const
{
	return textureID == b.textureID && flipU == b.flipU && flipV == b.flipV;
}