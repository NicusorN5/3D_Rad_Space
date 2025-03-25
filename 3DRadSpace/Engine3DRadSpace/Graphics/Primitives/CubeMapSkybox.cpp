#include "CubeMapSkybox.hpp"
#include "Box.hpp"
#include "../../Content/ShaderManager.hpp"
#include "..\Shaders\BasicTextured.hpp"
using namespace Engine3DRadSpace::Graphics::Shaders;

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

CubeMapSkybox::CubeMapSkybox(GraphicsDevice* device, std::array<Texture2D, 6> &&faces)
{
	std::array<VertexPositionUV, 4> px_vert =
	{
		//px
		VertexPositionUV{ Vector3(1, 1, 1), Vector2(0, 0) }, // 0
		VertexPositionUV{ Vector3(1, 1, -1), Vector2(1, 0) }, // 1
		VertexPositionUV{ Vector3(1, -1, 1), Vector2(0, 1) }, // 2
		VertexPositionUV{ Vector3(1, -1, -1), Vector2(1, 1) }, // 3
	};

	std::array<unsigned, 6> face_indices =
	{
		2, 1, 0,
		3, 1, 3
	};

	auto create_face = [&](unsigned index, std::span<VertexPositionUV> vertices, std::span<unsigned> indices)
	{
		auto mesh = new ModelMeshPart(
			std::static_pointer_cast<Effect>(ShaderManager::LoadShader<BasicTextured>(device)),
			device,
			vertices,
			indices
		);
		_faces[index].reset(mesh);

		_faces[index]->Textures.emplace_back(std::make_unique<Texture2D>(std::move(faces[index])));
		_faces[index]->TextureSamplers.emplace_back(std::make_unique<SamplerState>(device));
	};

	create_face(0u, px_vert, face_indices);
}

void CubeMapSkybox::Draw3D()
{
	_faces[0]->Transform = Model * View * Projection;
	_faces[0]->Draw();
}
