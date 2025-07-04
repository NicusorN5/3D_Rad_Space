#include "IShader.hpp"
#include "../Core/Logging.hpp"

#ifdef USING_DX11
#pragma comment(lib,"d3dcompiler.lib")
#endif

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

Array_ValidConstantBuffers IShader::_validConstantBuffers(unsigned &numConstantBuffers)
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

void IShader::_compileShader(const char *source, const char* target)
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

void IShader::_compileShaderFromFile(const char* path, const char* target)
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

IShader::IShader(GraphicsDevice *Device, const char *shaderSourceCode, const char *entry_function, ShaderFeatureLevel fl):
	_device(Device),
	_entry(entry_function),
	_featureLevel(fl),
	_constantBuffers({nullptr}),
	_shaderBlob(nullptr),
	_errorBlob(nullptr)
{
}

IShader::IShader(GraphicsDevice *Device, const std::filesystem::path &path, const char *entry_function, ShaderFeatureLevel fl) :
	_device(Device),
	_entry(entry_function),
	_featureLevel(fl),
	_constantBuffers({nullptr}),
	_shaderBlob(nullptr),
	_errorBlob(nullptr)
{
}

void IShader::SetData(unsigned index, const void *data, unsigned dataSize)
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


ShaderFeatureLevel IShader::GetFeatureLevel()
{
	return _featureLevel;
}

std::string IShader::GetEntryName()
{
	return std::string(_entry);
}

const char* IShader::GetCompilationErrorsAndWarnings()
{
	if(this->_errorBlob == nullptr) return nullptr;
	return static_cast<const char*>(this->_errorBlob->GetBufferPointer());
}