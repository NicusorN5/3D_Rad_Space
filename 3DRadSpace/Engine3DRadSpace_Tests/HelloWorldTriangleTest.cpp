#include "pch.h"
#include <Engine3DRadSpace/Games/Game.hpp>
#include <Engine3DRadSpace/Graphics/IVertexBuffer.hpp>
#include <Engine3DRadSpace/Graphics/IShaderCompiler.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Content;

class TriangleTest : public Game
{
	Effect* _triangleShader;
	std::unique_ptr<IVertexBuffer> _triangleBuffer;
public:
	TriangleTest();

	void Initialize() override;
	void Load() override;
	void Update() override;
	void Draw3D() override;

	int frameCount = 0;
};

TriangleTest::TriangleTest():
	Game("Triangle Test", 800, 600, false),
	_triangleShader(nullptr)
{

}

void TriangleTest::Initialize()
{
	std::array<VertexPositionColor, 3> triangle =
	{
		VertexPositionColor{Vector3(0.0,0.5,0.0), Colors::Red},
		VertexPositionColor{Vector3(0.5,-0.5,0.0), Colors::Green},
		VertexPositionColor{Vector3(-0.5,-0.5,0.0), Colors::Blue}
	};

	_triangleBuffer = Device->CreateVertexBuffer<VertexPositionColor>(triangle, BufferUsage::ReadOnlyGPU);
}

void TriangleTest::Load()
{
	constexpr std::string_view shaderPath = "Data\\Shaders\\PositionColor_NoMat.hlsl";

	ShaderDescFile vs(shaderPath, "VS_Main", ShaderType::Vertex);
	ShaderDescFile ps(shaderPath, "PS_Main", ShaderType::Fragment);

	ShaderDesc* effect[2] = { &vs, &ps };

	_triangleShader = Device->ShaderCompiler()->CompileEffect(effect).first;
}

void TriangleTest::Update()
{
}

void TriangleTest::Draw3D()
{
	if (frameCount == 1) Exit();
	frameCount++;

	auto cmd = Device->ImmediateContext();

	_triangleShader->SetAll();
	cmd->SetTopology(VertexTopology::TriangleList);
	cmd->DrawVertexBuffer(_triangleBuffer.get());
	cmd->SaveBackBufferToFile("Triangle.png");
	//TODO: Check if the saved image is matching with a expected image
}

TEST(EngineCoreTests, HelloTriangle)
{
	TriangleTest t;
	t.Run();
	EXPECT_TRUE(true);
}