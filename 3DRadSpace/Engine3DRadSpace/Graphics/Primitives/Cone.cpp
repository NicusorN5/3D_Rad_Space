#include "Cone.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Cone::Cone(IGraphicsDevice* device, float radius, float height, unsigned resolution, const Math::Color& color) : IPrimitive(device)
{
	resolution = std::max(3u, resolution);

	_vertices = device->CreateVertexBuffer<VertexPositionColor>(CreateConeVertices(radius, height, resolution, color), BufferUsage::ReadOnlyGPU_WriteOnlyCPU);

	auto ind = CreateConeIndices(resolution);
	_indices = device->CreateIndexBuffer(ind);
}

[[nodiscard]] std::vector<VertexPositionColor> Cone::CreateConeVertices(float radius, float height, unsigned resolution, const Math::Color& color)
{
	std::vector<VertexPositionColor> triangles;
	triangles.reserve(resolution + 2);

	triangles.emplace_back(Vector3(0, 0, 0), color);
	triangles.emplace_back(Vector3(0, height, 0), color);

	float dtheta = 2 * std::numbers::pi_v<float> / resolution;

	for(unsigned i = 0; i < resolution; i++)
	{
		float theta = dtheta * i;
		triangles.emplace_back(Vector3(radius * cosf(theta), 0, radius * sinf(theta)), color);
	}

	return triangles;
}

[[nodiscard]] std::vector<unsigned> Cone::CreateConeIndices(unsigned resolution)
{
	std::vector<unsigned> indices;
	indices.reserve(6 * resolution);
	
	//Generate cone
	for(unsigned i = 0; i < resolution; i++)
	{
		std::initializer_list<unsigned> tri = {1, (i + 2), 2 + ((i + 1) % resolution)};
		indices.insert(indices.end(), tri.begin(), tri.end());
	}

	//Generate base
	for(unsigned i = 0; i < resolution; i++)
	{
		std::initializer_list<unsigned> tri{0, 2 + ((i + 1) % resolution), (i + 2)};
		indices.insert(indices.end(), tri.begin(), tri.end());
	}

	return indices;
}