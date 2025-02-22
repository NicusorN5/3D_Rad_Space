#include "PostProcessEffect.hpp"

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
	_vertex(device, fl),
	_backbuffer_copy(nullptr)
{
}

PostProcessEffect::PostProcessEffect(
	GraphicsDevice* device,
	const std::filesystem::path &path,
	const char* entryFunction, 
	ShaderFeatureLevel fl
) : 
	IFragmentShader(device, path, entryFunction, fl),
	_vertex(device, fl),
	_backbuffer_copy(nullptr)
{
}

void PostProcessEffect::Apply()
{	
	//create a full screen quad and apply the shader to it.
	_device->SetScreenQuad();
	_device->SetShader(&_vertex);

	this->SetTexture(0, _backbuffer_copy);
	this->SetTexture(1, _device->GetDepthBuffer().GetDepthTexture());
	SetShader();
}

void PostProcessEffect::Draw()
{
	_device->SetTopology(VertexTopology::TriangleList);
	_device->DrawScreenQuad();
}

PostProcessEffect::PostProcessVertex::PostProcessVertex(GraphicsDevice* device, ShaderFeatureLevel fl) :
	IVertexShader(
		device, 
		_elements, 
		std::filesystem::path("Data\\Shaders\\PostProcessBase.hlsl"),
		"PostProcessBase_Main",
		fl
	)
{
}

std::span<InputLayoutElement> PostProcessEffect::PostProcessVertex::InputLayout()
{
	return _elements;
}
