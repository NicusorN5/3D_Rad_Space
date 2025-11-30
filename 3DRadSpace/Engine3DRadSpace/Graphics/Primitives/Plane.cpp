#include "Plane.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Plane::Plane(IGraphicsDevice* device, const Color& color, const Math::Vector2& size) :
	IPrimitive(device)
{
	auto vertices = CreateVertices(color, size);
	_vertices = device->CreateVertexBuffer<VertexPositionColor>(vertices, BufferUsage::ReadOnlyGPU);

	auto indices = CreateIndices();
	_indices = device->CreateIndexBuffer(indices);
}

std::array<VertexPositionColor, 4> Plane::CreateVertices(const Color& color, const Math::Vector2& size)
{
	std::array<VertexPositionColor, 4> vertices;

	Vector2 s(size * 0.5f);
	//							+z
	//						    /\              
	//				1			|              2
	//							|
	//							|
	// -------------------------+------------------------> +x
	//							|
	//							|
	//				0			|              3

	vertices[0] = VertexPositionColor(Vector3(-s.X, 0, -s.Y), color);
	vertices[1] = VertexPositionColor(Vector3(-s.X, 0, +s.Y), color);
	vertices[2] = VertexPositionColor(Vector3(+s.X, 0, +s.Y), color);
	vertices[3] = VertexPositionColor(Vector3(+s.X, 0, -s.Y), color);

	return vertices;
}

std::array<unsigned, 6> Primitives::Plane::CreateIndices()
{
	//Counter-clockwise ordered.
	return { 0, 2, 1, 0, 3, 2 };
}
