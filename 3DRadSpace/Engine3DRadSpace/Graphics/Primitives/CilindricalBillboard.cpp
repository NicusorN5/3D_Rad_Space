#include "CilindricalBillboard.hpp"
#include "../../Content/ShaderManager.hpp"
#include "../Shaders/BasicTextured.hpp"
#include "Plane.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

CilindricalBillboard::CilindricalBillboard(GraphicsDevice *device) :
	_device(device),
	Texture(nullptr)
{
	auto shader = Content::ShaderManager::LoadShader<BasicTextured>(device);
	auto vertices = CreateVertices();
	auto indices = Plane::CreateIndices();

	auto plane = new ModelMeshPart(
		std::static_pointer_cast<Effect>(shader), 
		device,
		std::span<VertexPositionUV>(vertices),
		indices
	);
	_plane.reset(plane);
}

Matrix4x4 CilindricalBillboard::_mvp() const noexcept
{
	//auto v = Matrix4x4::Invert(View);
	auto v = View;

	Vector3 cam_pos(v.M41, v.M42, v.M43);
	Vector3 x_axis(v.M11, v.M21, v.M31);
	Vector3 y_axis(v.M11, v.M21, v.M31);
	Vector3 z_axis(v.M11, v.M21, v.M31);
	
	Vector3 fwd = cam_pos + z_axis;
	Vector3 up = cam_pos + y_axis;
	Vector3 right = cam_pos + x_axis;

	auto model = Matrix4x4::CreateCilindricalBillboard(Position, cam_pos, up, fwd, Axis, std::nullopt);
	return model * View * Projection;
}

std::array<VertexPositionUV, 4> CilindricalBillboard::CreateVertices()
{
	std::array<VertexPositionUV, 4> plane;

	Vector2 s(0.5f);

	//See Plane.cpp
	plane[0] = VertexPositionUV(Vector3(-s.X, 0, -s.Y), Vector2(0,1));
	plane[1] = VertexPositionUV(Vector3(-s.X, 0, +s.Y), Vector2(0,0));
	plane[2] = VertexPositionUV(Vector3(+s.X, 0, +s.Y), Vector2(0,1));
	plane[3] = VertexPositionUV(Vector3(+s.X, 0, -s.Y), Vector2(1,1));

	return plane;
}

void CilindricalBillboard::Draw3D()
{
	_plane->Transform = _mvp();
	_plane->GetShaders()->GetPixelShader()->SetTexture(0, Texture);
	_plane->Draw();
}

