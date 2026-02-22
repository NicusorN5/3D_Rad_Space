#include "Arrow.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Arrow::Arrow(IGraphicsDevice* device, const Vector2& size, const Math::Color& color) : LineStrip(device, CreateArrowVertices(size.X, size.Y, color))
{
}

[[nodiscard]] std::vector<VertexPositionColor> Arrow::CreateArrowVertices(float width, float height, const Math::Color& color)
{
	//Starting at (0,0,0) pointing at (0,0,-1)
	//
	//       /1\
	//      / | \
	//     2--|--3
	//        |
	//        |
	//        |
	//        0

	std::initializer_list<VertexPositionColor> verts =
	{
		VertexPositionColor(Vector3(0,0,0), color),
		VertexPositionColor(Vector3(0, 0, -height), color),
		VertexPositionColor(Vector3(width, 0, -height + width), color),
		VertexPositionColor(Vector3(-width, 0, -height + width), color),
		VertexPositionColor(Vector3(0, 0, -height), color), // 1 = 4
	};

	return std::vector<VertexPositionColor>(verts);
}