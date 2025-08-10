#include "Sphere.hpp"
#include "../Shaders/ShaderManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

Sphere::Sphere(GraphicsDevice *device, float radius, Color color, unsigned resolution):
	IPrimitive(device),
	_radius(radius)
{
	using std::numbers::pi;

	if (resolution <= 1) resolution = 2;

	std::vector<VertexPositionColor> sphere_points( static_cast<size_t>( 2 + (resolution / (radius * 2 * pi)) ) );

	double dt = 2 * pi / resolution; //delta theta - NOT delta time.
	double dh = 2 * radius / resolution; //delta height

	unsigned k = 0; //iterator for indices

	unsigned numIndices = 2;
	//Generate sphere points from down to up.
	for(double h = -radius + dh; h <= radius - dh; h += dh)
	{
		//local radius(r,h) = sqrt( r ^ 2 - h ^2) graphed is a semicircle , for all r : radius(r,h) >= 0
		for(double theta = 0, local_radius = sqrt(pow(radius,2) - pow(h,2)); theta < 2 * std::numbers::pi; theta += dt, ++numIndices)
		{
			sphere_points.emplace_back(Vector3(
					float(local_radius * cos(theta)),
					float(h),
					float(local_radius * sin(theta))
				), 
				color 
			);
		}
	}

	//
	sphere_points.emplace_back(Vector3::UnitY() * radius, color); 
	_vertices = std::make_unique<VertexBufferV<VertexPositionColor>>(device, sphere_points);

	//Create indices...
	std::vector<unsigned> sphere_indices;
	sphere_indices.push_back(0);

	unsigned i = 0; //current index
	unsigned n = 0; // should be 2 * pi / resolution, but I think increasing it one by one could be safer regarding floating point loss of precision.
	unsigned m = 0; // should be 2 * height, same story as "n".

	//Create indices for the first row connected to the first point:
	for(double theta = 0,h = -radius + dh, local_radius = sqrt(pow(radius, 2) - pow(h, 2)); theta < 2 * std::numbers::pi; theta += dt, ++i, ++n)
	{
		sphere_indices.insert(sphere_indices.end(), { 0, i + 1, i + 2 });
	}
	sphere_indices.insert(sphere_indices.end(), { n,0,1 }); // insert last triangle of the first row.

	//Create indices for quads that are on the surface of the sphere.
	
	i = 0;
	unsigned j = 0;

	for(double h = -radius + dh; h <= radius - dh; h += dh, ++m)
	{
		for(double theta = 0, h = -radius + dh, local_radius = sqrt(pow(radius, 2) - pow(h, 2)); theta <= 2 * std::numbers::pi; theta += dt, ++i)
		{
			auto index_fn = [](unsigned i, unsigned j, unsigned width)
			{
				//plus 1 counts the first added index.
				return (width * j) + i + 1;
			};

			/*
				a -- b
				|  / |
				| /  |
				c----d

				c -> b -> a
				c -> d -> b
			*/
			auto i_a = index_fn(i, j, n);
			auto i_b = index_fn(i + 1, j, n);
			auto i_c = index_fn(i, j + 1, n);
			auto i_d = index_fn(i + 1, j + 1, n);

			sphere_indices.insert(sphere_indices.end(),
				{
					i_c, i_b, i_a,
					i_c, i_d, i_b 
				}
			);
		}
	}

	//TODO: Add last indices.
	_indices = std::make_unique<IndexBuffer>(device, sphere_indices);
}

float Sphere::GetRadius() const noexcept
{
	return _radius;
}

void Sphere::Draw3D()
{
	_shader->SetBasic();
	_shader->SetTransformation(_mvp());
	_device->SetTopology(VertexTopology::TriangleList);
	_device->DrawVertexBufferWithindices(_vertices.get(), _indices.get());
}