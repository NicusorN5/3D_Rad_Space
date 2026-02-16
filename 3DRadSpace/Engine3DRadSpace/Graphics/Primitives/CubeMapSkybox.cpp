#include "CubeMapSkybox.hpp"
#include "../IGraphicsDevice.hpp"
#include "../IShaderCompiler.hpp"
#include "../../Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;


CubeMapSkybox::CubeMapSkybox(IGraphicsDevice* device, std::array<ITexture2D*, 6> &faces) : IPrimitive(device, nullptr)
{
	_compileShader(device->ShaderCompiler());
	_create();

	_texture = device->CreateTextureCube(faces);
}

void CubeMapSkybox::_compileShader(IShaderCompiler* compiler)
{
	std::array<ShaderDesc*, 2> skyboxEffectDesc{};

	constexpr const char* skyboxShaderPath = "Data\\Shaders\\Skybox.hlsl";

	auto vsSkybox = ShaderDescFile(
		skyboxShaderPath,
		"VS_Main",
		ShaderType::Vertex
	);

	auto psSkybox = ShaderDescFile(
		skyboxShaderPath,
		"PS_Main",
		ShaderType::Fragment
	);

	skyboxEffectDesc[0] = &vsSkybox;
	skyboxEffectDesc[1] = &psSkybox;

	auto compileResult = compiler->CompileEffect(skyboxEffectDesc);
	if(compileResult.second.Succeded == false)
	{
		throw Exception("Failed to compile Skybox shader!" + compileResult.second.Log);
	}

	_shader = compileResult.first;
}

void CubeMapSkybox::_create()
{
	_vertices = _device->CreateVertexBuffer<VertexPosition>(CreateVertices(), BufferUsage::ReadOnlyGPU);

	auto indices = CreateIndices();
	_indices = _device->CreateIndexBuffer(indices);
}

CubeMapSkybox::CubeMapSkybox(IGraphicsDevice* device, const std::filesystem::path& dds) : IPrimitive(device, nullptr)
{
	_compileShader(device->ShaderCompiler());
	_create();

	_texture = device->CreateTextureCube(dds);
}

CubeMapSkybox::CubeMapSkybox(std::nullptr_t) : IPrimitive(nullptr, nullptr)
{
}

std::array<VertexPosition, 8> CubeMapSkybox::CreateVertices()
{
	return std::array<VertexPosition, 8>
	{
		VertexPosition{ Vector3(-1, -1, -1) },
		VertexPosition{ Vector3(1, -1, -1) },
		VertexPosition{ Vector3(1,  1, -1) },
		VertexPosition{ Vector3(-1,  1, -1) },
		VertexPosition{ Vector3(-1, -1,  1) },
		VertexPosition{ Vector3(1, -1,  1) },
		VertexPosition{ Vector3(1,  1,  1) },
		VertexPosition{ Vector3(-1,  1,  1) }
	};
}

std::array<unsigned, 36> CubeMapSkybox::CreateIndices()
{
	return std::array<unsigned, 36>
	{
		// Front face (+Z)
		4, 5, 6,
		4, 6, 7,

		// Back face (-Z)
		1, 0, 3,
		1, 3, 2,

		// Right face (+X)
		5, 1, 2,
		5, 2, 6,

		// Left face (-X)
		0, 4, 7,
		0, 7, 3,

		// Top face (+Y)
		7, 6, 2,
		7, 2, 3,

		// Bottom face (-Y)
		0, 1, 5,
		0, 5, 4
	};
}

void CubeMapSkybox::Draw3D()
{
	//_device->ImmediateContext()->UnbindDepthBuffer();

	_device->CreateDepthStencilState()

	_device->ImmediateContext()->SetDepthStencilState();

	_shader->operator[](1)->SetTexture(0u, _texture.get());

	IPrimitive::Draw3D();

	//_device->ImmediateContext()->SetDepthStencilBuffer(nullptr);
}