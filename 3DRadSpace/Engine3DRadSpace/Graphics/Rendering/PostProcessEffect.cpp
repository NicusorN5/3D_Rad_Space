#include "PostProcessEffect.hpp"
#include "../RenderTarget.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

PostProcessEffect::PostProcessEffect(
	GraphicsDevice* device,
	const char* shaderSource,
	const char* entryFunction, 
	ShaderFeatureLevel fl
) : 
	IFragmentShader(device, shaderSource, entryFunction, fl),
	_vertex(device, fl)
{
}

void PostProcessEffect::Apply()
{
	//TODO : create a full screen quad and apply the shader to it.
	_device->SetScreenQuad();
	_device->SetShader(&_vertex);
	
	auto backbuffer = _device->GetBackBuffer(0);
	this->SetTexture(0, dynamic_cast<Texture2D*>(backbuffer.get()) );
	SetShader();
}

void Engine3DRadSpace::Graphics::Rendering::PostProcessEffect::Draw()
{
	_device->DrawScreenQuad();
}

PostProcessEffect::PostProcessVertex::PostProcessVertex(GraphicsDevice* device, ShaderFeatureLevel fl) :
	IVertexShader(device, _elements, "Data\\Shaders\\PostProcessBase_Main.hlsl", "PostProcessBase_Main", fl)
{
}

std::span<InputLayoutElement> PostProcessEffect::PostProcessVertex::InputLayout()
{
	return _elements;
}
