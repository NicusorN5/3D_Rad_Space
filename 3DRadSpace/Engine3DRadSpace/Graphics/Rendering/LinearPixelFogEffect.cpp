/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/Rendering/LinearPixelFogEffect.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "LinearPixelFogEffect.hpp"
#include "../DepthStencilBuffer.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;

LinearPixelFogEffect::LinearPixelFogEffect(GraphicsDevice* device) : PostProcessEffect(
	device,
	std::filesystem::path("Data\\Shaders\\LinearFogSS.hlsl"), //shader filename
	"PS_Main" //fragment shader function
), 
	FogColor(1.0f,1.0f,1.0f,1.0f),
	FogBegin(0.0f), 
	FogEnd(1.0f)
{
}

void LinearPixelFogEffect::Apply()
{
	PostProcessEffect::Apply();
	
	struct alignas(16) FogData
	{
		Color FogColor;
		float FogBegin;
		float FogEnd;
	} fogData;

	fogData.FogColor = FogColor;
	fogData.FogBegin = FogBegin;
	fogData.FogEnd = FogEnd;

	this->SetData(0, &fogData, sizeof(FogData));

	auto depthBuffer = _device->GetDepthBuffer().GetDepthTexture();
	
	auto backbuffer = _device->GetBackBuffer();
	Texture2D& backBuffer = *backbuffer;

	std::array<Texture2D*, 2> textures = { &backBuffer, depthBuffer};

	this->SetTextures(textures);
}
