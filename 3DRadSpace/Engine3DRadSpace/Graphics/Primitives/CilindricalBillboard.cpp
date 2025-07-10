#include "CilindricalBillboard.hpp"
#include "../../Content/ShaderManager.hpp"
#include "../Shaders/BasicTextured.hpp"
#include "Plane.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;

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

std::array<VertexPositionUV, 4> CilindricalBillboard::CreateVertices()
{
	std::array<VertexPositionUV, 4> plane =
	{

	};
	return plane;
}

void CilindricalBillboard::Draw3D()
{
	_plane->Draw();
}

