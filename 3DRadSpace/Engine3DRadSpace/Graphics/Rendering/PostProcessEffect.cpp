#include "PostProcessEffect.hpp"
#include "../IGraphicsDevice.hpp"
#include "../IShaderCompiler.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

PostProcessEffect::PostProcessEffect(
	IGraphicsDevice* device,
	const ShaderDesc& desc
) :
	_device(device)
{
	auto desc = ShaderDescFile(
		"Data\\Shaders\\PostProcessBase.hlsl",
		"PostProcessBase_Main",
		ShaderType::Vertex
	);

	auto vs = _device->ShaderCompiler()->Compile(&desc);
	if (vs.second.Succeded)
	{
		this->_vertex = vs.first;
	}
}

void PostProcessEffect::Apply()
{	
	//create a full screen quad and apply the shader to it.
	_device->SetScreenQuad();
	_device->SetShader(_vertex);

	this->SetTexture(0, _backbuffer_copy);
	this->SetTexture(1, _depthBuffer_copy);

	_device->SetShader(this);
}

void PostProcessEffect::SetTexture(unsigned index, ITexture2D* texture)
{
	_vertex->SetTexture(index, texture);
	_effect->SetTexture(index, texture);
}

void PostProcessEffect::SetSampler(unsigned index, ISamplerState* sampler)
{
	_vertex->SetSampler(index, sampler);
	_effect->SetSampler(index, sampler);
}

void PostProcessEffect::SetData(unsigned index, const void* data, size_t size)
{
	_effect->SetData(index, data, size);
}

void PostProcessEffect::Draw()
{
	_device->SetTopology(VertexTopology::TriangleList);
	_device->DrawScreenQuad();
}

void* PostProcessEffect::GetHandle() const noexcept
{
	return _vertex->GetHandle();
}

IGraphicsDevice* PostProcessEffect::GetGraphicsDevice() const noexcept
{
	return _device;
}