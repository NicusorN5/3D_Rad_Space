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

	auto c = _device->ShaderCompiler()->Compile(&desc);
	if (c.second.Succeded)
	{

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

void PostProcessEffect::Draw()
{
	_device->SetTopology(VertexTopology::TriangleList);
	_device->DrawScreenQuad();
}
