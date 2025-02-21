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
		float FogBegin;
		float FogEnd;
		float _padding[2];
		Color FogColor;
	} fogData;

	fogData.FogColor = FogColor;
	fogData.FogBegin = FogBegin;
	fogData.FogEnd = FogEnd;

	this->SetData(0, &fogData, sizeof(fogData));
}
