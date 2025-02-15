/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/Shaders/SpriteShader.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "SpriteShader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;

static inline std::array<InputLayoutElement, 3> sprite_elements =
{
	InputLayoutElement::Position_Vec2,
	InputLayoutElement::TextureCoordinate2D,
	InputLayoutElement::Color
};

SpriteShader::VertexShader::VertexShader(GraphicsDevice *device) :
	IVertexShader(device, sprite_elements, std::filesystem::path("Data\\Shaders\\Sprite.hlsl"), "VS_Main")
{
}

std::span<InputLayoutElement> SpriteShader::VertexShader::InputLayout()
{
	return sprite_elements;
}

SpriteShader::PixelShader::PixelShader(GraphicsDevice *device) : IFragmentShader(device, std::filesystem::path("Data\\Shaders\\Sprite.hlsl"), "PS_Main")
{
}

SpriteShader::SpriteShader(GraphicsDevice *device) :
	Effect(device, new VertexShader(device), new PixelShader(device))
{
}

void SpriteShader::SetTexture(Texture2D *texture)
{
	_vertex->SetTexture(0, texture);
	_pixel->SetTexture(0, texture);
}

void SpriteShader::SetSamplerState(SamplerState *sampler)
{
	_vertex->SetSampler(0, sampler);
	_pixel->SetSampler(0, sampler);
}
