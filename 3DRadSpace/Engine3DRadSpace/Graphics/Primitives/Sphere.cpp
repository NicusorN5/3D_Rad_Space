#include "Sphere.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Sphere::Sphere(IGraphicsDevice *device, float radius, Color color, unsigned resolution):
	IPrimitive(device),
	_radius(radius)
{
	auto sphere_points = CreateSphereVertices(radius, resolution, color);
	_vertices = device->CreateVertexBuffer<VertexPositionColor>(sphere_points, BufferUsage::ReadOnlyGPU);

	auto sphere_indices = CreateSphereIndices(resolution);
	_indices = device->CreateIndexBuffer(sphere_indices);
}

float Sphere::GetRadius() const noexcept
{
	return _radius;
}

[[nodiscard]] std::vector<VertexPositionColor> Sphere::CreateSphereVertices(float radius, unsigned resolution, const Math::Color& color)
{
	auto slices = resolution;
	auto stacks = resolution;

	std::vector<VertexPositionColor> v;
	v.reserve(2 + slices * (stacks - 1));

	// top pole
	v.emplace_back(Vector3(0, radius, 0), color);

	float dphi = std::numbers::pi_v<float> / stacks;
	float dtheta = 2 * std::numbers::pi_v<float> / slices;

	// rings
	for(unsigned stack = 1; stack < stacks; ++stack)
	{
		float phi = dphi * stack;

		float y = radius * cosf(phi);
		float r = radius * sinf(phi);

		for(unsigned slice = 0; slice < slices; ++slice)
		{
			float theta = dtheta * slice;

			float x = r * cosf(theta);
			float z = r * sinf(theta);

			v.emplace_back(Vector3(x, y, z), color);
		}
	}

	// bottom pole
	v.emplace_back(Vector3(0, -radius, 0), color);

	return v;
}

[[nodiscard]] std::vector<unsigned> Sphere::CreateSphereIndices(unsigned resolution)
{
	//https://github.com/caosdoar/spheres/blob/master/src/spheres.cpp

	auto slices = resolution;
	auto stacks = resolution;

	std::vector<unsigned> indices;
	indices.reserve(6 * slices * stacks);

	unsigned top = 0;
	unsigned bottom = 1 + slices * (stacks - 1);

	// top cap
	for(unsigned i = 0; i < slices; ++i)
	{
		unsigned next = (i + 1) % slices;

		std::initializer_list<unsigned> tr = {top, i + 1, next + 1};
		indices.insert(indices.end(), tr);
	}

	// middle
	for(unsigned stack = 0; stack < stacks - 2; ++stack)
	{
		unsigned ringStart = 1 + stack * slices;
		unsigned nextRingStart = ringStart + slices;

		for(unsigned slice = 0; slice < slices; ++slice)
		{
			unsigned next = (slice + 1) % slices;

			unsigned a = ringStart + slice;
			unsigned b = ringStart + next;
			unsigned c = nextRingStart + slice;
			unsigned d = nextRingStart + next;

			std::initializer_list<unsigned> quad =
			{
				a, c, d,
				a, d, b
			};
			
			indices.insert(indices.end(), quad);
		}
	}

	// bottom cap
	unsigned lastRing = bottom - slices;

	for(unsigned i = 0; i < slices; ++i)
	{
		unsigned next = (i + 1) % slices;

		std::initializer_list<unsigned> tr{bottom, lastRing + next, lastRing + i};
		indices.insert(indices.end(), tr);
	}

	return indices;
}