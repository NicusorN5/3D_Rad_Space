#include "CubeMapSkybox.hpp"
#include "Box.hpp"
#include "../Shaders/ShaderManager.hpp"
#include "..\Shaders\SkyboxShader.hpp"
#include "../../Objects/Camera.hpp"

using namespace Engine3DRadSpace::Graphics::Shaders;

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

CubeMapSkybox::CubeMapSkybox(GraphicsDevice* device, std::array<Texture2D, 6> &&faces)
{
	std::array<VertexPositionUV, 4> px_vert =
	{
		//px
		VertexPositionUV{ Vector3(1, 1, -1), Vector2(1, 0) }, // 0
		VertexPositionUV{ Vector3(1, 1, 1), Vector2(0, 0) }, // 1
		VertexPositionUV{ Vector3(1, -1, -1), Vector2(1, 1) }, // 2
		VertexPositionUV{ Vector3(1, -1, 1), Vector2(0, 1) }, // 3
	};

	std::array<VertexPositionUV, 4> nx_vert =
	{
		//nx
		VertexPositionUV{ Vector3(-1, 1, -1), Vector2(0, 0) }, // 0
		VertexPositionUV{ Vector3(-1, 1, 1), Vector2(1, 0) }, // 1
		VertexPositionUV{ Vector3(-1, -1, -1), Vector2(0, 1) }, // 2
		VertexPositionUV{ Vector3(-1, -1, 1), Vector2(1, 1) }, // 3
	};

	std::array<VertexPositionUV, 4> py_vert =
	{
		//py
		VertexPositionUV{ Vector3(-1, 1, -1), Vector2(0, 0) }, // 0
		VertexPositionUV{ Vector3(1, 1, -1), Vector2(1, 0) }, // 1
		VertexPositionUV{ Vector3(-1, 1, 1), Vector2(0, 1) }, // 2
		VertexPositionUV{ Vector3(1, 1, 1), Vector2(1, 1) }, // 3
	};

	std::array<VertexPositionUV, 4> ny_vert =
	{
		//ny
		VertexPositionUV{ Vector3(-1, -1, -1), Vector2(0, 1) }, // 0
		VertexPositionUV{ Vector3(1, -1, -1), Vector2(1, 1) }, // 1
		VertexPositionUV{ Vector3(-1, -1, 1), Vector2(0, 0) }, // 2
		VertexPositionUV{ Vector3(1, -1, 1), Vector2(1, 0) }, // 3
	};

	std::array<VertexPositionUV, 4> pz_vert =
	{
		//pz
		VertexPositionUV{ Vector3(-1, 1, 1), Vector2(0, 0) }, // 0
		VertexPositionUV{ Vector3(1, 1, 1), Vector2(1, 0) }, // 1
		VertexPositionUV{ Vector3(-1, -1, 1), Vector2(0, 1) }, // 2
		VertexPositionUV{ Vector3(1, -1, 1), Vector2(1, 1) }, // 3
	};

	std::array<VertexPositionUV, 4> nz_vert =
	{
		//nz
		VertexPositionUV{ Vector3(-1, 1, -1), Vector2(1, 0) }, // 0
		VertexPositionUV{ Vector3(1, 1, -1), Vector2(0, 0) }, // 1
		VertexPositionUV{ Vector3(-1, -1, -1), Vector2(1, 1) }, // 2
		VertexPositionUV{ Vector3(1, -1, -1), Vector2(0, 1) }, // 3
	};

	std::array<unsigned, 6> face_indices_frontface =
	{
		2, 1, 0,
		3, 1, 2
	};

	std::array<unsigned, 6> face_indices_backface =
	{
		0, 1, 2,
		2, 1, 3
	};

	auto create_face = [&](unsigned index, std::span<VertexPositionUV> vertices, std::span<unsigned> indices)
	{
		auto mesh = new ModelMeshPart(
			std::static_pointer_cast<Effect>(ShaderManager::LoadShader<SkyboxShader>(device)),
			device,
			vertices,
			indices
		);
		_faces[index].reset(mesh);

		_faces[index]->Textures.emplace_back(std::make_unique<Texture2D>(std::move(faces[index])));
		_faces[index]->TextureSamplers.emplace_back(std::make_unique<SamplerState>(std::move(SamplerState::LinearClamp(device))));
	};

	create_face(0, px_vert, face_indices_backface);
	create_face(1, nx_vert, face_indices_frontface);
	create_face(2, py_vert, face_indices_frontface);
	create_face(3, ny_vert, face_indices_backface);
	create_face(4, pz_vert, face_indices_frontface);
	create_face(5, nz_vert, face_indices_backface);
}

CubeMapSkybox::CubeMapSkybox(GraphicsDevice* device,const std::filesystem::path& dds)
{
	//TODO: Implement DDS loading
}

CubeMapSkybox::CubeMapSkybox(std::nullptr_t)
{
}

//void CubeMapSkybox::SetTransformFromCamera(const Camera& camera)
//{
//	float s = camera.FarPlaneDistance * 0.5f;
//	Model = Matrix4x4::CreateScale(Vector3(s, s, s)) * Matrix4x4::CreateTranslation(camera.Position);
//	View = camera.GetViewMatrix();
//	Projection = camera.GetProjectionMatrix();
//}

void CubeMapSkybox::Draw3D()
{
	for(std::size_t i = 0; i < _faces.size(); i++)
	{
		_faces[i]->Transform = Model * View * Projection;
		_faces[i]->Draw();
	}
}
