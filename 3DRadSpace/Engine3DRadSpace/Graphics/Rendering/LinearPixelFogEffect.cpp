#include "LinearPixelFogEffect.hpp"
#include "../DepthStencilBuffer.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;

LinearPixelFogEffect::LinearPixelFogEffect(GraphicsDevice* device) : PostProcessEffect(
	device,
	"Data\\Shaders\\LinearFogSS.hlsl", //shader filename
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
	
	struct FogData
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
	this->SetTexture(1, depthBuffer.get());
}
