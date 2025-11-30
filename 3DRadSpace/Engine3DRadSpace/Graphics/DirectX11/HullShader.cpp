#include "HullShader.hpp"
#include "ShaderCompilationError.hpp"
#include "GraphicsDevice.hpp"
#include "SamplerState.hpp"
#include "../Core/FixedArray.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;

void HullShader::_createShader()
{
	HRESULT r = _device->_device->CreateHullShader(
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		nullptr,
		_shader.GetAddressOf()
	);

	if(FAILED(r)) throw ShaderCompilationError("Failed to create a hull shader!");

#ifdef _DEBUG
	const char shaderName[] = "HullShader::_shader";
	_shader->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(shaderName) - 1, shaderName);
#endif
}

const char * HullShader::_determineTarget(ShaderFeatureLevel f)
{
	switch(f)
	{
		case ShaderFeatureLevel::DX_V4:
			return "hs_4_0";
		case ShaderFeatureLevel::DX_V4_1:
			return "hs_4_1";
		case ShaderFeatureLevel::DX_V5:
			return "hs_5_0";
		case ShaderFeatureLevel::DX_V6:
			return "hs_6_0";
		default:
			return nullptr;
			break;
	}
}

HullShader::HullShader(GraphicsDevice *device, const char *shaderSource, const char *hsEntry, ShaderFeatureLevel fl):
	ShaderBase(device, shaderSource, hsEntry, _determineTarget(fl))
{
	_compileShader(shaderSource, _determineTarget(fl));
	_createShader();
}

HullShader::HullShader(GraphicsDevice *device, const std::filesystem::path &path, const char *hsEntry, ShaderFeatureLevel fl):
	ShaderBase(device, path, hsEntry, _determineTarget(fl))
{
	_compileShaderFromFile(path.string().c_str(), _determineTarget(fl));
	_createShader();
}

void HullShader::SetTexture(unsigned index, ITexture2D *texture)
{
	if(texture == nullptr)
		return;

	auto dxTexture2D = static_cast<Texture2D*>(texture);
	_device->_context->HSSetShaderResources(index, 1, dxTexture2D->_resourceView.GetAddressOf());
}

void HullShader::SetTextures(std::span<ITexture2D*> textures)
{
	FixedArray<ID3D11ShaderResourceView*> views(textures.size());

	for (size_t i = 0; i < textures.size() && i < D3D11_COMMONSHADER_INPUT_RESOURCE_REGISTER_COUNT; i++)
	{
		views[i] = static_cast<ID3D11ShaderResourceView*>(textures[i]->GetHandle());
	}

	_device->_context->HSSetShaderResources(0, textures.size(), &views[0]);
}

void HullShader::SetSampler(unsigned index, ISamplerState *samplerState)
{
	auto dxSamplerState = static_cast<SamplerState*>(samplerState);
	_device->_context->HSSetSamplers(index, 1, dxSamplerState->_samplerState.GetAddressOf());
}

void HullShader::SetShader()
{
	ShaderBase::SetShader();

	unsigned i;
	auto validConstantBuffers = this->_validConstantBuffers(i);
	_device->_context->HSSetConstantBuffers(0, i, validConstantBuffers.data());

	_device->_context->HSSetShader(_shader.Get(), nullptr, 0);
}

void* HullShader::GetHandle() const noexcept
{
	return static_cast<void*>(_shader.Get());
}