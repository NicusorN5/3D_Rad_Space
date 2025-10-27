#include "FragmentShader.hpp"
#include "ShaderCompilationError.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

void FragmentShader::_createShader()
{
#ifdef USING_DX11
	HRESULT r = _device->_device->CreatePixelShader(
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		nullptr,
		_shader.GetAddressOf());

	if(FAILED(r)) throw ShaderCompilationError("Failed to create a pixel shader!");

#ifdef _DEBUG
	const char shaderName[] = "FragmentShader::_shader";
	_shader->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(shaderName), shaderName);
#endif
#endif
}

const char * FragmentShader::_determineTarget()
{
	switch(_featureLevel)
	{
		case ShaderFeatureLevel::DX_V4:
			return "ps_4_0";
		case ShaderFeatureLevel::DX_V4_1:
			return "ps_4_1";
		case ShaderFeatureLevel::DX_V5:
			return "ps_5_0";
		case ShaderFeatureLevel::DX_V6:
			return "ps_6_0";
		default:
			return nullptr;
	}
}

FragmentShader::FragmentShader(GraphicsDevice *device, const char *shaderSource, const char *entryFunction, ShaderFeatureLevel fl):
	IShader(device, shaderSource, entryFunction, fl)
{
	_compileShader(shaderSource, _determineTarget());
	_createShader();
}

FragmentShader::FragmentShader(GraphicsDevice *device, const std::filesystem::path &path, const char *entryFunction, ShaderFeatureLevel fl):
	IShader(device, path, entryFunction, fl)
{
	_compileShaderFromFile(path.string().c_str(), _determineTarget());
	_createShader();
}

void FragmentShader::SetTexture(unsigned index, Texture2D *texture)
{
	if(texture == nullptr)
		return;
#ifdef USING_DX11
	_device->_context->PSSetShaderResources(index, 1, texture->_resourceView.GetAddressOf());
#endif // USING_DX11
}

void FragmentShader::SetTextures(std::span<Texture2D*> textures)
{
#ifdef USING_DX11
	std::unique_ptr<ID3D11ShaderResourceView* []> srvs = std::make_unique<ID3D11ShaderResourceView* []>(textures.size());
	auto len = textures.size();

	for(decltype(len) i = 0; i < len; i++)
	{
		srvs[i] = textures[i]->_resourceView.Get();
	}

	_device->_context->PSSetShaderResources(0, len, srvs.get());
#endif // USING_DX11
}

void FragmentShader::SetSampler(unsigned index, SamplerState *samplerState)
{
#ifdef USING_DX11
	_device->_context->PSSetSamplers(0, 1, samplerState->_samplerState.GetAddressOf());
#endif
}

void FragmentShader::SetShader()
{
#ifdef USING_DX11
	unsigned i;
	auto validConstantBuffers = this->_validConstantBuffers(i);
	_device->_context->PSSetConstantBuffers(0, i, validConstantBuffers.data());

	_device->_context->PSSetShader(_shader.Get(), nullptr, 0);
#endif
}

void* FragmentShader::GetHandle() const noexcept
{
#ifdef USING_DX11
	return static_cast<void*>(_shader.Get());
#endif
}
