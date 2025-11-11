#include "ShaderBase.hpp"
#include "../Core/Logging.hpp"
#include "GraphicsDevice.hpp"

#pragma comment(lib,"d3dcompiler.lib")

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Logging;

ShaderBase::Array_ValidConstantBuffers ShaderBase::_validConstantBuffers(unsigned &numConstantBuffers)
{
#ifdef USING_DX11
	const unsigned maxConstBuffers = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
	Array_ValidConstantBuffers ppConstantBuffers = {nullptr};

	unsigned &i = numConstantBuffers;
	for(i = 0; i < maxConstBuffers; i++)
	{
		ID3D11Buffer *constBuffer = _constantBuffers[i].Get();
		if(constBuffer == nullptr) break;

		ppConstantBuffers[i] = constBuffer;
	}

	return ppConstantBuffers;
#endif
}

void ShaderBase::_compileShader(const char *source, const char* target)
{
#ifdef _WIN32
#ifdef _DEBUG
	const UINT shaderFlags = D3DCOMPILE_DEBUG;
#else
	const UINT shaderFlags = 0;
#endif

	HRESULT r = D3DCompile(
		source,
		strlen(source),
		nullptr,
		nullptr,
		nullptr,
		_entry,
		target,
		shaderFlags,
		0,
		&_shaderBlob,
		&_errorBlob
	);
	if (_errorBlob.Get() != nullptr)
	{
		if(FAILED(r))
		{
			//MessageBoxA(nullptr, static_cast<char*>(_errorBlob->GetBufferPointer()), "Shader compilation error!", MB_ICONERROR);
			throw Exception(std::string("Shader compilation failure! \r\n") + static_cast<char*>(_errorBlob->GetBufferPointer()));
		}
	}
	else SetLastWarning(Warning(r, (char*)_errorBlob->GetBufferPointer(), 2, nullptr));
#endif
}

void ShaderBase::_compileShaderFromFile(const char* path, const char* target)
{
#ifdef _WIN32
	wchar_t wpath[_MAX_PATH]{ 0 };
	MultiByteToWideChar(CP_ACP, 0, path, (int)strlen(path), wpath, _MAX_PATH);

#ifdef _DEBUG
	const UINT shaderFlags = D3DCOMPILE_DEBUG;
#else
	const UINT shaderFlags = 0;
#endif

	HRESULT r = D3DCompileFromFile(
		wpath,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		_entry,
		target,
		shaderFlags,
		0,
		&_shaderBlob,
		&_errorBlob
	);
	if(_errorBlob.Get() == nullptr && FAILED(r)) throw Exception(std::string("Shader file not found! \r\n Path:") + path);
	else
	{
		if (_errorBlob.Get() != nullptr)
			SetLastWarning(Warning(r, (char*)_errorBlob->GetBufferPointer(), 2, nullptr));

		if(FAILED(r))
		{
			//MessageBoxA(nullptr, static_cast<char*>(_errorBlob->GetBufferPointer()), "Shader compilation error!", MB_ICONERROR);
			throw Exception(std::string("Shader compilation failure! \r\n") + static_cast<char*>(_errorBlob->GetBufferPointer()));
		}
	}
#endif
}

ShaderBase::ShaderBase(GraphicsDevice *Device, const char *shaderSourceCode, const char *entry_function, ShaderFeatureLevel fl):
	_device(Device),
	_entry(entry_function),
	_featureLevel(fl),
	_constantBuffers({nullptr}),
	_shaderBlob(nullptr),
	_errorBlob(nullptr)
{
	_compileShader(shaderSourceCode, entry_function);
	_reflectShader();
}

ShaderBase::ShaderBase(GraphicsDevice *Device, const std::filesystem::path &path, const char *entry_function, ShaderFeatureLevel fl) :
	_device(Device),
	_entry(entry_function),
	_featureLevel(fl),
	_constantBuffers({nullptr}),
	_shaderBlob(nullptr),
	_errorBlob(nullptr)
{
	_compileShaderFromFile(path.string().c_str(), entry_function);
	_reflectShader();
}

void ShaderBase::SetData(unsigned index, const void *data, size_t dataSize)
{
#ifdef USING_DX11
	if (_constantBuffers[index].Get() == nullptr)
	{
		D3D11_BUFFER_DESC constantBufferDesc{};
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.ByteWidth = dataSize;
		constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

		D3D11_SUBRESOURCE_DATA res{};
		res.pSysMem = data;

		HRESULT r = _device->_device->CreateBuffer(&constantBufferDesc, &res, _constantBuffers[index].ReleaseAndGetAddressOf());
		if (FAILED(r)) throw Exception("Failed to create a constant buffer for a shader!");
#ifdef _DEBUG
		std::string constantBufferName = "IShader::constantBuffer[";
		constantBufferName += std::to_string(index) + ']';

		_constantBuffers[index]->SetPrivateData(WKPDID_D3DDebugObjectName, unsigned(constantBufferName.length()), constantBufferName.c_str());
#endif
	}
	else
	{
		D3D11_MAPPED_SUBRESOURCE res;
		HRESULT r = _device->_context->Map(_constantBuffers[index].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &res);
		if (FAILED(r)) throw Exception("Failed to write the shader data!");
		memcpy(res.pData, data, dataSize);
		_device->_context->Unmap(_constantBuffers[index].Get(), 0);
	}
#endif
}


ShaderFeatureLevel ShaderBase::GetFeatureLevel()
{
	return _featureLevel;
}

std::string ShaderBase::GetEntryName()
{
	return std::string(_entry);
}

const char* ShaderBase::GetCompilationErrorsAndWarnings()
{
	if(this->_errorBlob == nullptr) return nullptr;
	return static_cast<const char*>(this->_errorBlob->GetBufferPointer());
}



void ShaderBase::_reflectShader()
{
	HRESULT r = D3DReflect(
		this->_shaderBlob->GetBufferPointer(),
		this->_shaderBlob->GetBufferSize(),
		IID_PPV_ARGS(&_reflector)
	);
	if (FAILED(r)) throw Exception("Failed to reflect the shader!");

	for (int idxCbuffer = 0; ; idxCbuffer++)
	{
		auto cbuffer = _reflector->GetConstantBufferByIndex(idxCbuffer);
		if (cbuffer == nullptr)
			break;
	
		D3D11_SHADER_BUFFER_DESC buffDesc{};
		r = cbuffer->GetDesc(&buffDesc);
		if (FAILED(r))
			break;

		unsigned numVariables = buffDesc.Variables;
		size_t buffSize = buffDesc.Size;

		for (unsigned idxVariable = 0; idxVariable < numVariables; idxVariable++)
		{
			auto variable = cbuffer->GetVariableByIndex(0);
			if (variable == nullptr)
				break;

			D3D11_SHADER_VARIABLE_DESC varDesc{};
			variable->GetDesc(&varDesc);
		}
	}
}

std::vector<Reflection::IReflectedField*> ShaderBase::GetVariables() const
{
	std::vector<Reflection::IReflectedField*> r;
	for (int i = 0; i < _reflectedFields.size(); i++)
	{
		r.emplace_back(_reflectedFields[i].get());
	}
	return r;
}

void ShaderBase::Set(const std::string& name, const void* data, size_t dataSize)
{
	for (auto &var : _reflectedFields)
	{
		if (var->FieldName() == name)
		{
			//var->Set(nullptr, data);
			return;
		}
	}
}

IGraphicsDevice* ShaderBase::GetGraphicsDevice() const noexcept
{
	return _device;
}