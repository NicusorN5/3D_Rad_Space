#include "MeshHighlight.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

MeshHighlight::VertexShader::VertexShader(GraphicsDevice* device):
	IVertexShader(device, element, std::filesystem::path("Data\\Shaders\\HighlightMesh.hlsl"), "VS_Main")
{
}

MeshHighlight::PixelShader::PixelShader(GraphicsDevice* device) :
	IFragmentShader(device, std::filesystem::path("Data\\Shaders\\HighlightMesh.hlsl"), "PS_Main")
{
}

std::span<InputLayoutElement> MeshHighlight::VertexShader::InputLayout()
{
	return std::span<InputLayoutElement>(element);
}

MeshHighlight::MeshHighlight(GraphicsDevice* device):
	Effect(device, new VertexShader(device), new PixelShader(device))
{
}

void MeshHighlight::SetTransformation(const Matrix4x4& matrix)
{
	_vertex->SetData(0, static_cast<const void*>(&matrix), sizeof(Matrix4x4));
	_pixel->SetData(0, static_cast<const void*>(&matrix), sizeof(Matrix4x4));
}

void MeshHighlight::SetColor(Color c)
{
	_pixel->SetData(1, static_cast<const void*>(&c), sizeof(Color));
}
