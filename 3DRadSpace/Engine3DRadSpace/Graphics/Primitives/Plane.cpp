/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/Primitives/Plane.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "Plane.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Plane::Plane(GraphicsDevice* device, const Color& color, const Math::Vector2& size) :
	IPrimitive(device)
{
	auto vertices = CreateVertices(color, size);
	_vertices = std::make_unique<VertexBufferV<VertexPositionColor>>(device, vertices);

	auto indices = CreateIndices();
	_indices = std::make_unique<IndexBuffer>(device, indices);
}

std::array<VertexPositionColor, 4> Plane::CreateVertices(const Color& color, const Math::Vector2& size)
{
	std::array<VertexPositionColor, 4> vertices;

	Vector2 s(size * 0.5f);
	//							+y
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

void Plane::Draw3D()
{
	_shader->SetBasic();
	_shader->SetTransformation(_mvp());

	_device->SetTopology(VertexTopology::TriangleList);
	_device->DrawVertexBufferWithindices(_vertices.get(), _indices.get());
}
