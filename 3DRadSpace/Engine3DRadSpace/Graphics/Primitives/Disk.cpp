#include "Disk.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Disk::Disk(IGraphicsDevice* device, float radius, unsigned resolution, const Math::Color& color) : IPrimitive(device)
{
	_vertices = device->CreateVertexBuffer<VertexPositionColor>(CreateDiskVertices(radius, resolution, color), BufferUsage::ReadOnlyGPU_WriteOnlyCPU);

	auto ind = CreateDiskIndices(resolution);
	_indices = device->CreateIndexBuffer(ind);
}

[[nodiscard]] std::vector<VertexPositionColor> Disk::CreateDiskVertices(float radius, unsigned resolution, const Math::Color& color)
{
	resolution = std::max(2u, resolution);

	std::vector<VertexPositionColor> triangles;
	triangles.reserve(resolution + 1);

	triangles.emplace_back(Vector3(0, 0, 0), color);

	float dtheta = 2 * std::numbers::pi_v<float> / resolution;

	for(unsigned i = 0; i < resolution; i++)
	{
		float theta = dtheta * i;
		triangles.emplace_back(Vector3( radius * cosf(theta), 0, radius * sinf(theta)), color);
	}

	return triangles;
}

[[nodiscard]] std::vector<unsigned> Disk::CreateDiskIndices(unsigned resolution)
{
	std::vector<unsigned> indices;
	indices.reserve(3 * resolution);

	for(unsigned i = 0; i < resolution; i++)
	{
		std::initializer_list<unsigned> tri = {0, i, i + 1};
		indices.insert(indices.end(), tri.begin(), tri.end());
	}

	std::initializer_list<unsigned> lastTriangle = {0, resolution, 1};

	indices.insert(indices.end(), lastTriangle.begin(), lastTriangle.end());

	return indices;
}