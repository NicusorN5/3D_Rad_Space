#include "Circle.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Algorithms;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Circle::Circle(GraphicsDevice* device, float radius, Color color, unsigned resolution) :
	Lines(device, CreateCircleVertices(radius, resolution, color)),
	_radius(radius)
{
}

FixedArray<VertexPositionColor> Circle::CreateCircleVertices(float radius, unsigned resolution, Color color)
{
	resolution = std::max(resolution, 3u); //create a circle from a minimum of three points.

	FixedArray<VertexPositionColor> vertices(resolution);

	float dp = 2 * std::numbers::pi_v<float> / resolution ; //delta phi
	unsigned i = 0;
	float phi = 0; //angle
	for(; i < resolution - 1; ++i, phi += dp)
	{
		vertices[i] = VertexPositionColor(
			Vector3(cos(phi), 0, sin(phi)),
			color
		);
	}
	vertices[resolution - 1] = vertices[0];

	return vertices;
}

void Circle::Draw3D()
{
	_swapRasterizer();
	_shader->SetAll();
	_shader->SetTransformation(_mvp());

	_device->SetTopology(VertexTopology::LineStrip);
	_vertices->Draw();
	_restoreRasterizer();
}

float Circle::GetRadius() const noexcept
{
	return _radius;
}
