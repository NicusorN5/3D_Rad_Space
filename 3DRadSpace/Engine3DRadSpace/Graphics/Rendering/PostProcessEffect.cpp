#include "PostProcessEffect.hpp"
#include "../IGraphicsDevice.hpp"
#include "../IShaderCompiler.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

PostProcessEffect::PostProcessEffect(
	IGraphicsDevice* device,
	ShaderDesc& effectDesc
) :
	_vertex(nullptr),
	_device(device)
{
	//Compile base vertex effect
	auto desc = ShaderDescFile(
		"Data\\Shaders\\PostProcessBase.hlsl",
		"PostProcessBase_Main",
		ShaderType::Vertex
	);

	auto vs = _device->ShaderCompiler()->Compile(&desc);
	if (vs.second.Succeded)
	{
		_vertex = vs.first;
	}

	//Compile given post process effect
	auto ps = _device->ShaderCompiler()->Compile(&effectDesc);
	if (ps.second.Succeded)
	{
		_effect = vs.first;
	}
}

void PostProcessEffect::Apply()
{	
	//create a full screen quad and apply the shader to it.
	auto cmd = _device->ImmediateContext();

	cmd->SetShader(_vertex);

	this->SetTexture(0, _backbuffer_copy);
	this->SetTexture(1, _depthBuffer_copy);

	cmd->SetShader(this);
}

void PostProcessEffect::SetTexture(unsigned index, ITexture2D* texture)
{
	_effect->SetTexture(index, texture);
}

void PostProcessEffect::SetTextures(std::span<ITexture2D*> textures)
{
	_effect->SetTextures(textures);
}

void PostProcessEffect::SetSampler(unsigned index, ISamplerState* sampler)
{
	_effect->SetSampler(index, sampler);
}

void PostProcessEffect::SetData(unsigned index, const void* data, size_t size)
{
	_effect->SetData(index, data, size);
}

void PostProcessEffect::Draw()
{
	auto cmd = _device->ImmediateContext();

	cmd->SetTopology(VertexTopology::TriangleList);
	cmd->DrawVertexBuffer(_device->GetScreenQuad());
}

void* PostProcessEffect::GetHandle() const noexcept
{
	return _vertex->GetHandle();
}

IGraphicsDevice* PostProcessEffect::GetGraphicsDevice() const noexcept
{
	return _device;
}

std::vector<Reflection::IReflectedField*> PostProcessEffect::GetVariables() const
{
	return _effect->GetVariables();
}

void PostProcessEffect::Set(const std::string& name, const void* data, size_t dataSize)
{
	_effect->Set(name, data, dataSize);
}

std::string PostProcessEffect::GetEntryName()
{
	return _effect->GetEntryName();
}

const char* PostProcessEffect::GetCompilationErrorsAndWarnings()
{
	return _effect->GetCompilationErrorsAndWarnings();
}

void PostProcessEffect::SetShader()
{
	_effect->SetShader();
}