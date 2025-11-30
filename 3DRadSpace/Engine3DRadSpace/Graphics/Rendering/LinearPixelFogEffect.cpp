#include "LinearPixelFogEffect.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;
using namespace Engine3DRadSpace::Math;

static ShaderDescFile linearPixelFogShaderDesc(
	"Data\\Shaders\\LinearFogSS.hlsl",
	"PS_Main",
	ShaderType::Fragment
);

LinearPixelFogEffect::LinearPixelFogEffect(IGraphicsDevice* device) : PostProcessEffect(
	device,
	linearPixelFogShaderDesc
), 
	FogColor(1.0f, 1.0f, 1.0f, 1.0f),
	FogBegin(0.0f), 
	FogEnd(1.0f),
	NearPlaneDistance(0.1f),
	FarPlaneDistance(0.8f)
{
}

void LinearPixelFogEffect::Apply()
{
	PostProcessEffect::Apply();
	
	struct alignas(16) FogData
	{
		float FogBegin;
		float FogEnd;
		float Near;
		float Far;
		Color FogColor;
	} fogData;

	fogData.FogColor = FogColor;
	fogData.FogBegin = FogBegin;
	fogData.FogEnd = FogEnd;

	fogData.Near = NearPlaneDistance;
	fogData.Far = FarPlaneDistance;

	this->SetData(0, &fogData, sizeof(fogData));
}
