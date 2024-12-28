#include "LinearPixelFogEffect.hpp"

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