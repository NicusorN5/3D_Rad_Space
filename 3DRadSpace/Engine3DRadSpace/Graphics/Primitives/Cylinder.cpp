#include "Cylinder.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Cylinder::Cylinder(IGraphicsDevice *device, float radius, float height, float tessellation, Color color) :
	IPrimitive(device)
{
	auto verts = CreateCylinderVertices(radius, height, tessellation, color);
	this->_vertices = device->CreateVertexBuffer<VertexPositionColor>(verts, BufferUsage::ReadOnlyGPU_WriteOnlyCPU);
}

[[nodiscard]] std::vector<VertexPositionColor> Cylinder::CreateCylinderVertices(float radius, float height, unsigned resolution, Color color)
{
	resolution = std::min(2u, resolution);

	auto r = std::vector<VertexPositionColor>(resolution * 3 + 7);

	float top = height / 2;
	float bottom = -height / 2;

	//Top ring
	auto topCenter = VertexPositionColor(Vector3(0, top, 0), color);
	r[0] = topCenter;

	float dtheta = 2 * std::numbers::pi_v<float> / resolution;
	
	r.push_back(topCenter);

	for(unsigned i = 0; i < resolution; i += 2)
	{
		auto theta = dtheta * i;
		r.emplace_back(Vector3(radius * cosf(theta), top, radius * sinf(theta)), color);
		++i; theta = dtheta * i;
		r.emplace_back(Vector3(radius * cosf(theta), top, radius * sinf(theta)), color);
		r.push_back(topCenter);
	}

	r.emplace_back(Vector3(0, top, 0), color); //Finish top ring
	r.emplace_back(Vector3(0, bottom, 0), color); //Begin middle quads

	for(unsigned i = 1; i < resolution; i ++)
	{
		auto theta = dtheta * i;
		r.emplace_back(Vector3(radius * cosf(theta), top, radius * sinf(theta)), color);
		r.emplace_back(Vector3(radius * cosf(theta), bottom, radius * sinf(theta)), color);
	}

	r.emplace_back(Vector3(0, top, 0), color); 
	r.emplace_back(Vector3(0, bottom, 0), color);

	//Bottom ring
	r.emplace_back(Vector3(0, bottom, 0), color);
	//r.emplace_back(Vector3(radius, bottom, 0), color); // cos(0) = 1, sin(0) = 0
	for(unsigned i = 0; i < resolution; i += 2)
	{
		auto theta = dtheta * i;
		r.emplace_back(Vector3(radius * cosf(theta), bottom, radius * sinf(theta)), color);
		++i; theta = dtheta * i;
		r.emplace_back(Vector3(radius * cosf(theta), bottom, radius * sinf(theta)), color);
		r.emplace_back(Vector3(0, bottom, 0), color);
	}

	r.emplace_back(Vector3(radius, bottom, 0), color); //Finish bottom ring

	return r;
}

void Cylinder::Draw3D()
{
	auto mvp = _mvp();

	_shader->SetAll();
	_shader->operator[](0)->SetData(0, &mvp, sizeof(mvp));

	auto cmd = _device->ImmediateContext();

	cmd->SetTopology(VertexTopology::TriangleStrip);
	cmd->DrawVertexBufferWithindices(_vertices.get(), _indices.get());
}
