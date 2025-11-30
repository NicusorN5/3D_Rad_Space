#include "Cylinder.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Cylinder::Cylinder(IGraphicsDevice *device, float radius, float height, float tessellation) :
	IPrimitive(device)
{
}

[[nodiscard]] FixedArray<VertexPositionColor> Cylinder::CreateCylinderVertices(float radius, float height, unsigned resolution, Color color)
{
	auto r = FixedArray<VertexPositionColor>(resolution * 2 + 2);

	float top = height / 2;
	float bottom = -height / 2;

	r[0] = VertexPositionColor(Vector3(0, top, 0), color);
	
	float dp = 2 * std::numbers::pi_v<float> / resolution;

	for(unsigned i = 0; i < resolution ; i++)
	{
		float angle = (2 * std::numbers::pi_v<float>) * i / resolution;
		r[i + 2] = VertexPositionColor(Vector3(radius * std::cos(angle), top, radius * std::sin(angle)), color);
		r[resolution + i + 2] = VertexPositionColor(Vector3(radius * std::cos(angle), top, radius * std::sin(angle)), color);
	}

	return r;
}

[[nodiscard]] FixedArray<unsigned> Engine3DRadSpace::Graphics::Primitives::Cylinder::CreateCylinderIndices(unsigned resolution)
{
	auto r = FixedArray<unsigned>(resolution * 12);

	//generate top faces.
	auto add_triangle = [&r](size_t pos, std::span<unsigned,3> i)
	{
		r[pos] = i[0];
		r[pos + 1] = i[1];
		r[pos + 2] = i[2];
	};

	auto vi = 0u;

	for(auto vi = 0u, i = 0u; vi < 3 * (resolution - 1); vi += 3, ++i)
	{
		std::array<unsigned, 3> top_triangle = {
			0,
			i + 2,
			i + 3 
		};
		add_triangle(vi, top_triangle);
	}

	std::array<unsigned, 3> last_top_triangle = {
		0,
		resolution + 1,
		2
	};
	add_triangle(vi, last_top_triangle);

	//generate middle faces.

	auto add_quad = [&r](size_t pos, std::span<unsigned, 4> i)
	{
		r[pos] = i[0];
		r[pos + 1] = i[1];
		r[pos + 2] = i[2];
		r[pos + 3] = i[3];
	};

	for(auto vi = 3 * resolution, i = 0u; vi < 6 * (resolution - 1); vi += 4, ++i)
	{
		std::array<unsigned, 4> quad = {
			i + 2,
			i + 3,
			resolution + i + 3,
			resolution + i + 2
		};
		add_quad(vi, quad);
	}

	//add last quad

	std::array<unsigned, 4> last_quad = {

	};

	return r;
}
