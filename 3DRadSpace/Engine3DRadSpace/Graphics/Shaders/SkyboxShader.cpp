#include "SkyboxShader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

SkyboxShader::VertexShader::VertexShader(GraphicsDevice* device) :
	IVertexShader(device, elements, std::filesystem::path("Data\\Shaders\\Skybox.hlsl"), "VS_Main")
{
}

std::span<InputLayoutElement> SkyboxShader::VertexShader::InputLayout()
{
	return elements;
}

SkyboxShader::PixelShader::PixelShader(GraphicsDevice* device) :
	IFragmentShader(device, std::filesystem::path("Data\\Shaders\\Skybox.hlsl"), "PS_Main")
{
}

SkyboxShader::SkyboxShader(GraphicsDevice* device) :
	Effect(device, new VertexShader(device), new PixelShader(device))
{
}

void SkyboxShader::SetTransform(const Matrix4x4& m)
{
	_vertex->SetData(0, &m, sizeof(Matrix4x4));
}

void SkyboxShader::SetTexture(Texture2D* texture)
{
	_pixel->SetTexture(0, texture);
}

void SkyboxShader::SetSampler(SamplerState* state)
{
	_pixel->SetSampler(0, state);
}