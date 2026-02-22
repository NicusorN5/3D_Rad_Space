#include "Cylinder.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Cylinder::Cylinder(IGraphicsDevice *device, float radius, float height, unsigned tessellation, Color color) :
	IPrimitive(device)
{
	tessellation = std::max(3u, tessellation);

	auto verts = CreateCylinderVertices(radius, height, tessellation, color);
	this->_vertices = device->CreateVertexBuffer<VertexPositionColor>(verts, BufferUsage::ReadOnlyGPU_WriteOnlyCPU);

	auto indices = CreateCylinderIndices(tessellation);
	_indices = device->CreateIndexBuffer(indices);
}

[[nodiscard]] std::vector<VertexPositionColor> Cylinder::CreateCylinderVertices(float radius, float height, unsigned resolution, Color color)
{
	std::vector<VertexPositionColor> r;
	r.reserve(2 + 2 * resolution);

	float top = height / 2;
	float bottom = -height / 2;

	//Top ring
	float dtheta = 2 * std::numbers::pi_v<float> / resolution;
	
	r.emplace_back(Vector3(0, bottom, 0), color);
	r.emplace_back(Vector3(0, top, 0), color);

	for(unsigned i = 0; i < resolution; i++)
	{
		auto theta = dtheta * i;
		auto x = radius * cosf(theta);
		auto y = radius * sinf(theta);
		r.emplace_back(Vector3(x, bottom, y), color);
		r.emplace_back(Vector3(x, top, y), color);
	}
	return r;
}

[[nodiscard]] std::vector<unsigned> Cylinder::CreateCylinderIndices(unsigned resolution)
{
	std::vector<unsigned> indices;
	indices.reserve(12 * resolution);

	for(unsigned i = 0; i < resolution; ++i)
	{
		unsigned next = (i + 1) % resolution;

		unsigned bottom_i = 2 + i * 2;
		unsigned top_i = bottom_i + 1;

		unsigned bottom_next = 2 + next * 2;
		unsigned top_next = bottom_next + 1;

		std::initializer_list<unsigned> faces =
		{
			//quad
			bottom_i, top_next, top_i, // side triangle 1
			bottom_i, bottom_next, top_next, //side triangle 2
			0, bottom_next, bottom_i, //bottom face
			1, top_i, top_next // top face
		};

		indices.insert(indices.end(), faces.begin(), faces.end());
	}

	return indices;
}