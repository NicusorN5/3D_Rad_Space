#include "PostProcessEffect.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

PostProcessEffect::PostProcessEffect(
	GraphicsDevice* device,
	const char* shaderSource,
	const char* entryFunction, 
	ShaderFeatureLevel fl
) : IFragmentShader(device, shaderSource, entryFunction, fl)
{
}

void PostProcessEffect::Apply()
{
	//TODO : create a full screen quad and apply the shader to it.
	_device->SetScreenQuad();
	SetShader();
	_device->DrawScreenQuad();
}