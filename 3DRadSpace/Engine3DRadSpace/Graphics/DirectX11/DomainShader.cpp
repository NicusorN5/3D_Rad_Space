#include "DomainShader.hpp"
#include "ShaderCompilationError.hpp"
#include "GraphicsDevice.hpp"
#include "SamplerState.hpp"
#include "Texture1D.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;

const char *DomainShader::_determineTarget(ShaderFeatureLevel f)
{
	switch(f)
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
	ShaderBase(device, source, fnEntry, _determineTarget(fs))
{
	_compileShader(source, _determineTarget(fs));
	_createShader();
}

DomainShader::DomainShader(GraphicsDevice *device, const std::filesystem::path &path, const char *fnEntry, ShaderFeatureLevel fs):
	ShaderBase(device, path, fnEntry, _determineTarget(fs))
{
	_compileShaderFromFile(path.string().c_str(), _determineTarget(fs));
	_createShader();
}


void DomainShader::SetTexture(unsigned index, ITexture1D* texture)
{
	if(texture == nullptr)
		return;

	auto dxTexture = static_cast<Texture1D*>(texture);
	_device->_context->DSSetShaderResources(index, 1, dxTexture->_shaderResourceView.GetAddressOf());
}

void DomainShader::SetTextures(std::span<ITexture1D*> textures)
{
	std::unique_ptr<ID3D11ShaderResourceView* []> srvs = std::make_unique<ID3D11ShaderResourceView*[]>(textures.size());
	auto len = textures.size();

	for(decltype(len) i = 0; i < len; i++)
	{
		srvs[i] = static_cast<Texture1D*>(textures[i])->_shaderResourceView.Get();
	}

	_device->_context->DSSetShaderResources(0, len, srvs.get());
}

void DomainShader::SetTexture(unsigned index, ITexture2D *texture)
{
	if(texture == nullptr)
		return;

	auto dxTexture = static_cast<Texture2D*>(texture);
	_device->_context->DSSetShaderResources(index, 1, dxTexture->_resourceView.GetAddressOf());
}

void DomainShader::SetTextures(std::span<ITexture2D*> textures)
{
	std::unique_ptr<ID3D11ShaderResourceView* []> srvs = std::make_unique<ID3D11ShaderResourceView * []>(textures.size());
	auto len = textures.size();

	for (decltype(len) i = 0; i < len; i++)
	{
		srvs[i] = static_cast<Texture2D*>(textures[i])->_resourceView.Get();
	}

	_device->_context->DSSetShaderResources(0, len, srvs.get());
}

void DomainShader::SetSampler(unsigned index, ISamplerState *samplerState)
{
	auto dxSamplerState = static_cast<SamplerState*>(samplerState);
	_device->_context->DSSetSamplers(index, 1, dxSamplerState->_samplerState.GetAddressOf());
}

void DomainShader::SetShader()
{
	ShaderBase::SetShader();

	unsigned i;
	auto validConstantBuffers = this->_validConstantBuffers(i);
	_device->_context->DSSetConstantBuffers(0, i, validConstantBuffers.data());

	_device->_context->DSSetShader(_shader.Get(), nullptr, 0);
}

void* DomainShader::GetHandle() const noexcept
{
	return static_cast<void*>(_shader.Get());
}