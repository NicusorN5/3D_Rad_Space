#include "Sphere.hpp"
#include "../../Content/ShaderManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

Sphere::Sphere(GraphicsDevice *device, float radius, Color color, unsigned resolution):
	_device(device),
	_radius(radius)
{
	if (resolution <= 1) resolution = 2;

	std::vector<VertexPositionColor> sphere_points =
	{
		VertexPositionColor{Vector3::UnitY() * -radius, color }
	};

	std::vector<unsigned> sphere_indices;

	double dr = 2 * std::numbers::pi / resolution; //delta radius
	double dh = 2 * radius / resolution; //delta height

	unsigned k = 0; //iterator for indices

	//Generate sphere points from down to up.
	for(double h = -radius + dh; h <= radius - dh; h += dh)
	{
		//local radius(r,h) = sqrt( r ^ 2 - h ^2) graphed is a semicircle
		for(double theta = 0, local_radius = sqrt(pow(radius,2) - pow(h,2)); theta <= 2 * std::numbers::pi; theta += dr)
		{
			sphere_points.push_back(VertexPositionColor{
				Vector3(
					float(local_radius * cos(theta)),
					float(h),
					float(local_radius * sin(theta))
				), color }
			);
		}
	}

	sphere_points.push_back(VertexPositionColor(Vector3::UnitY() * radius, color));

	_vertices = std::make_unique<VertexBufferV<VertexPositionColor>>(device, sphere_points);

	_indices = std::make_unique<IndexBuffer>(device, sphere_indices);
	_shader = ShaderManager::LoadShader<BlankShader>(device);
}

float Engine3DRadSpace::Graphics::Primitives::Sphere::GetRadius() const
{
	return _radius;
}

void Sphere::Draw(Matrix4x4&view, Matrix4x4&projection, double dt)
{
	_shader->SetBasic();
	_device->SetTopology(VertexTopology::TriangleList);
	_device->DrawVertexBufferWithindices(_vertices.get(), _indices.get());
}
