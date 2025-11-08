#include "DomainShader.hpp"
#include "ShaderCompilationError.hpp"
#include "GraphicsDevice.hpp"
#include "SamplerState.hpp"
#include "../Core/FixedArray.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;

const char *DomainShader::_determineTarget()
{
	switch(_featureLevel)
	{
		case ShaderFeatureLevel::DX_V4:
			return "ds_4_0";
		case ShaderFeatureLevel::DX_V4_1:
			return "ds_4_1";
		case ShaderFeatureLevel::DX_V5:
			return "ds_5_0";
		case ShaderFeatureLevel::DX_V6:
			return "ds_6_0";
		default:
			return nullptr;
			break;
	}
}

void DomainShader::_createShader()
{
	HRESULT r = _device->_device->CreateDomainShader(
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		nullptr,
		_shader.GetAddressOf()
	);

	if(FAILED(r)) throw ShaderCompilationError("Failed to create a domain shader!");

#ifdef  _DEBUG
	const char shaderName[] = "DomainShader::_shader";
	_shader->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(shaderName) - 1, shaderName);
#endif //  _DEBUG
}

DomainShader::DomainShader(GraphicsDevice *device, const char *source, const char *fnEntry, ShaderFeatureLevel fs) :
	ShaderBase(device, source, fnEntry, fs)
{
	_compileShader(source, _determineTarget());
	_createShader();
}

DomainShader::DomainShader(GraphicsDevice *device, const std::filesystem::path &path, const char *fnEntry, ShaderFeatureLevel fs):
	ShaderBase(device, path, fnEntry, fs)
{
	_compileShaderFromFile(path.string().c_str(), _determineTarget());
	_createShader();
}

void DomainShader::SetTexture(unsigned index, ITexture2D *texture)
{
	if(texture == nullptr)
		return;

	auto dxTexture = static_cast<Texture2D*>(texture);
	_device->_context->DSSetShaderResources(index, 1, dxTexture->_resourceView.GetAddressOf());
}

void DomainShader::SetSampler(unsigned index, ISamplerState *samplerState)
{
	auto dxSamplerState = static_cast<SamplerState*>(samplerState);
	_device->_context->DSSetSamplers(index, 1, dxSamplerState->_samplerState.GetAddressOf());
}

void DomainShader::SetShader()
{
	unsigned i;
	auto validConstantBuffers = this->_validConstantBuffers(i);
	_device->_context->DSSetConstantBuffers(0, i, validConstantBuffers.data());

	_device->_context->DSSetShader(_shader.Get(), nullptr, 0);
}

void* DomainShader::GetHandle() const noexcept
{
	return static_cast<void*>(_shader.Get());
}