#pragma once
#include "LineStrip.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT Arrow : public LineStrip
	{
	public:
		Arrow(IGraphicsDevice *device, const Math::Vector2& size, const Math::Color& color);

		[[nodiscard]] std::vector<VertexPositionColor> CreateArrowVertices(float width, float height, const Math::Color& color);

		~Arrow() override = default;
	};
}