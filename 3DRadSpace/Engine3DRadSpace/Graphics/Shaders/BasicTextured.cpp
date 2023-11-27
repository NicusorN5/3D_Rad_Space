#include "BasicTextured.hpp"
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;

BasicTextured::VertexShader::VertexShader(GraphicsDevice* device) :
	IVertexShader(device, elements, std::filesystem::path("Data\\Shaders\\PositionNormalTangentUV.hlsl"), "VS_Main")
{
}

std::span<InputLayoutElement> BasicTextured::VertexShader::InputLayout()
{
	return elements;
}

BasicTextured::PixelShader::PixelShader(GraphicsDevice* device) :
	IPixelShader(device, std::filesystem::path("Data\\Shaders\\PositionNormalTangentUV.hlsl"), "PS_Main")
{
}


BasicTextured::BasicTextured(GraphicsDevice* device) : 
	Effect(device, new VertexShader(device), new PixelShader(device))
{
}

void BasicTextured::SetTransform(const Matrix4x4& m)
{
	_vertex->SetData(0, &m, sizeof(Matrix4x4));
}

void BasicTextured::SetTexture(Texture2D* texture)
{
	_vertex->SetTexture(0, texture);
}

void BasicTextured::SetSampler(SamplerState* state)
{
	_pixel->SetSampler(0, state);
}
