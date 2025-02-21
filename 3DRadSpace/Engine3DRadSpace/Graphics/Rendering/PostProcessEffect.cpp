#include "PostProcessEffect.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

/// <summary>
/// Texturebuffer used as output for post process effects.
/// </summary>
std::shared_ptr<RenderTarget> ppeff_render_surface;

std::shared_ptr<Texture2D> ppeff_backbuffer_cpy;

void PostProcessEffect::_setRenderSurface(GraphicsDevice* device)
{
	device->UnbindRenderTargetAndDepth(); //unbinds render target, so it can be copied into backbuffer_cpy

	//create and assign output render target.
	if(!ppeff_render_surface)
	{
		ppeff_render_surface = std::make_shared<RenderTarget>(device);
	}
	_renderSurface = ppeff_render_surface;

	//Create and assign a copy of the back buffer.
	if(!ppeff_backbuffer_cpy)
	{
		auto backbuffer = device->GetBackBufferTexture();
		ppeff_backbuffer_cpy = std::make_shared<Texture2D>(std::move(backbuffer->Clone()));
	}
	_bkbuff_cpy = ppeff_backbuffer_cpy;

	//upon resource creation assume the default render target and depth stencil buffers were set.
	//otherwise... - previously set RT and DSB are lost...
	device->SetRenderTargetAndDepth(nullptr, nullptr); 
}

PostProcessEffect::PostProcessEffect(
	GraphicsDevice* device,
	const char* shaderSource,
	const char* entryFunction, 
	ShaderFeatureLevel fl
) : 
	IFragmentShader(device, shaderSource, entryFunction, fl),
	_vertex(device, fl)
{
	_setRenderSurface(device);
}

PostProcessEffect::PostProcessEffect(
	GraphicsDevice* device,
	const std::filesystem::path &path,
	const char* entryFunction, 
	ShaderFeatureLevel fl
) : 
	IFragmentShader(device, path, entryFunction, fl),
	_vertex(device, fl)
{
	_setRenderSurface(device);
}

void PostProcessEffect::Apply()
{
	//unbind backbuffer, so it can be drawn into
	_device->SetRenderTargetAndDisableDepth(_renderSurface.get());
	_device->ClearRenderTarget(_renderSurface.get());

	//create a full screen quad and apply the shader to it.
	_device->SetScreenQuad();
	_device->SetShader(&_vertex);

	this->SetTexture(0, _bkbuff_cpy.get());
	SetShader();
}

void Engine3DRadSpace::Graphics::Rendering::PostProcessEffect::Draw()
{
	_device->SetTopology(VertexTopology::TriangleList);
	_device->DrawScreenQuad();
}

PostProcessEffect::~PostProcessEffect()
{
	//if there's only one reference remaining, it is from the global variables themselfs.
	//if(ppeff_render_surface.use_count() == 1)
	//	ppeff_render_surface.reset();

	//if(ppeff_backbuffer_cpy.use_count() == 1)
	//	ppeff_backbuffer_cpy.reset();
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
