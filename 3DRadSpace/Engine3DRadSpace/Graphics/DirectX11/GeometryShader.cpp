#include "GeometryShader.hpp"
#include "ShaderCompilationError.hpp"
#include "GraphicsDevice.hpp"
#include "SamplerState.hpp"
#include "../Core/FixedArray.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;

const char *GeometryShader::_determineTarget()
{
	switch(_featureLevel)
	{
		case ShaderFeatureLevel::DX_V4:
			return "gs_4_0";
		case ShaderFeatureLevel::DX_V4_1:
			return "gs_4_1";
		case ShaderFeatureLevel::DX_V5:
			return "gs_5_0";
		case ShaderFeatureLevel::DX_V6:
			return "gs_6_0";
		default:
			return nullptr;
			break;
	}
}

void GeometryShader::_createShader()
{
	HRESULT r = _device->_device->CreateGeometryShader(
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		nullptr,
		_shader.GetAddressOf()
	);

	if(FAILED(r)) throw ShaderCompilationError("Failed to create a domain shader!");

#ifdef _DEBUG
	const char shaderName[] = "IGeometryShader::_shader";
	_shader->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(shaderName) - 1, shaderName);
#endif
}

GeometryShader::GeometryShader(GraphicsDevice *device, const char *source, const char *fnEntry, ShaderFeatureLevel fs) :
	ShaderBase(device, source, fnEntry, fs)
{
	_compileShader(source, _determineTarget());
	_createShader();
}

GeometryShader::GeometryShader(GraphicsDevice *device, const std::filesystem::path &path, const char *fnEntry, ShaderFeatureLevel fs) :
	ShaderBase(device, path, fnEntry, fs)
{
	_compileShaderFromFile(path.string().c_str(), _determineTarget());
	_createShader();
}

void GeometryShader::SetTexture(unsigned index, ITexture2D *texture)
{
	if(texture == nullptr)
		return;

	auto dxTexture = static_cast<Texture2D*>(texture);
	_device->_context->GSSetShaderResources(index, 1, dxTexture->_resourceView.GetAddressOf());
}

void GeometryShader::SetTextures(std::span<ITexture2D*> textures)
{
	FixedArray<ID3D11ShaderResourceView*> views(textures.size());

	for (size_t i = 0; i < std::min(textures.size(), size_t(D3D11_COMMONSHADER_INPUT_RESOURCE_REGISTER_COUNT)); i++)
	{
		views[i] = static_cast<ID3D11ShaderResourceView*>(textures[i]->GetHandle());
	}

	_device->_context->GSSetShaderResources(0, textures.size(), &views[0]);
}

void GeometryShader::SetSampler(unsigned index, ISamplerState *samplerState)
{
	auto dxSamplerState = static_cast<DirectX11::SamplerState*>(samplerState);
	_device->_context->GSSetSamplers(index, 1, dxSamplerState->_samplerState.GetAddressOf());
}

void GeometryShader::SetShader()
{
	unsigned i;
	auto validConstantBuffers = this->_validConstantBuffers(i);
	_device->_context->GSSetConstantBuffers(0, i, validConstantBuffers.data());

	_device->_context->GSSetShader(_shader.Get(), nullptr, 0);
}

void* GeometryShader::GetHandle() const noexcept
{
	return static_cast<void*>(_shader.Get());
}

