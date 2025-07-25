#include "IVertexShader.hpp"
#include "../Core/Logging.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Graphics;

const char* IVertexShader::_determineTarget()
{
	switch(_featureLevel)
	{
		case ShaderFeatureLevel::DX_V4:
			return "vs_4_0";
		case ShaderFeatureLevel::DX_V4_1:
			return "vs_4_1";
		case ShaderFeatureLevel::DX_V5:
			return "vs_5_0";
		case ShaderFeatureLevel::DX_V6:
			return "vs_6_0";
		default:
			return nullptr;
			break;
	}
}

void IVertexShader::_createShader()
{
#ifdef USING_DX11
	HRESULT r = _device->_device->CreateVertexShader(
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		nullptr,
		_shader.ReleaseAndGetAddressOf()
	);

	if(FAILED(r)) throw std::exception("Failed to compile the shader!");
#ifdef _DEBUG
	const char shaderName[] = "IVertexShader::_shader";
	_shader->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(shaderName) - 1, shaderName);
#endif
#endif // USING_DX11
}

D3D11_INPUT_ELEMENT_DESC *IVertexShader::_generateInputElementDesc(std::span<InputLayoutElement> inputLayout)
{
#ifdef USING_DX11
	size_t numLayoutEntries = inputLayout.size();

	D3D11_INPUT_ELEMENT_DESC *elem = new D3D11_INPUT_ELEMENT_DESC[numLayoutEntries]{};
	if(elem == nullptr)
	{
		throw Exception("Failed to allocate heap memory for a D3D11_INPUT_ELEMENT_DESC array!");
	}

	unsigned posIndex = 0;
	//unsigned posTIndex = 0;
	unsigned colorIndex = 0;
	unsigned normalIndex = 0;
	unsigned tangentIndex = 0;
	unsigned bitangentIndex = 0;
	unsigned texCoordIndex = 0;
	unsigned blendIndicesIndex = 0;
	unsigned blendWeightIndex = 0;
	unsigned pointSizeIndex = 0;

	for(int i = 0; i < numLayoutEntries; i++)
	{
		switch(inputLayout[i])
		{
			case InputLayoutElement::Position_Vec2:
			{
				elem[i] =
				{
					"POSITION", //SemanticName
					posIndex, //SemanticIndex
					DXGI_FORMAT_R32G32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				posIndex++;
				break;
			}
			case InputLayoutElement::Position_Vec3:
			{
				elem[i] =
				{
					"POSITION", //SemanticName
					posIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				posIndex++;
				break;
			}
			case InputLayoutElement::Position_Vec4:
			{
				elem[i] =
				{
					"POSITION", //SemanticName
					posIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				posIndex++;
				break;
			}
			case InputLayoutElement::PositionTransformed_Vec3:
			{
				elem[i] =
				{
					"POSITIONT", //SemanticName
					0, //posTIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				//posTIndex++;
				break;
			}
			case InputLayoutElement::PositionTransformed_Vec4:
			{
				elem[i] =
				{
					"POSITIONT", //SemanticName
					0, //posTIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				//posTIndex++;
				break;
			}
			case InputLayoutElement::Color:
			{
				elem[i] =
				{
					"COLOR", //SemanticName
					colorIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				colorIndex++;
				break;
			}
			case InputLayoutElement::Normal_Vec3:
			{
				elem[i] =
				{
					"NORMAL", //SemanticName
					normalIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				normalIndex++;
				break;
			}
			case InputLayoutElement::Normal_Vec4:
			{
				elem[i] =
				{
					"NORMAL", //SemanticName
					normalIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				normalIndex++;
				break;
			}
			case InputLayoutElement::Tangent_Vec3:
			{
				elem[i] =
				{
					"TANGENT", //SemanticName
					tangentIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				tangentIndex++;
				break;
			}
			case InputLayoutElement::Tangent_Vec4:
			{
				elem[i] =
				{
					"TANGENT", //SemanticName
					tangentIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				tangentIndex++;
				break;
			}
			case InputLayoutElement::Bitangent_Vec3:
			{
				elem[i] =
				{
					"BITANGENT", //SemanticName
					bitangentIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				bitangentIndex++;
				break;
			}
			case InputLayoutElement::Bitangent_Vec4:
			{
				elem[i] =
				{
					"BITANGENT", //SemanticName
					bitangentIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				bitangentIndex++;
				break;
			}
			case InputLayoutElement::TextureCoordinate2D:
			{
				elem[i] =
				{
					"TEXCOORD", //SemanticName
					texCoordIndex, //SemanticIndex
					DXGI_FORMAT_R32G32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				texCoordIndex++;
				break;
			}
			case InputLayoutElement::TextureCoordinate3D:
			{
				elem[i] =
				{
					"TEXCOORD", //SemanticName
					texCoordIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				texCoordIndex++;
				break;
			}
			case InputLayoutElement::TextureCoordinate4D:
			{
				elem[i] =
				{
					"TEXCOORD", //SemanticName
					texCoordIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				texCoordIndex++;
				break;
			}
			case InputLayoutElement::BlendIndices:
			{
				elem[i] =
				{
					"BLENDINDICES", //SemanticName
					blendIndicesIndex, //SemanticIndex
					DXGI_FORMAT_R32_UINT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				blendIndicesIndex++;
				break;
			}
			case InputLayoutElement::BlendWeights:
			{
				elem[i] =
				{
					"BLENDWEIGHT", //SemanticName
					blendWeightIndex, //SemanticIndex
					DXGI_FORMAT_R32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				blendWeightIndex++;
				break;
			}
			case InputLayoutElement::PointSize:
			{
				elem[i] =
				{
					"PSIZE", //SemanticName
					blendWeightIndex, //SemanticIndex
					DXGI_FORMAT_R32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				blendWeightIndex++;
				break;
			}
			default:
				break;
		}
	}
	return elem;
#endif
}

void IVertexShader::_generateInputLayout(std::span<InputLayoutElement> inputLayout)
{
#ifdef USING_DX11
	D3D11_INPUT_ELEMENT_DESC *elements = _generateInputElementDesc(inputLayout);

	HRESULT r = _device->_device->CreateInputLayout(
		elements,
		static_cast<UINT>(inputLayout.size()),
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		&this->_inputLayout
	);
	delete[] elements;

#ifdef _DEBUG
	const char inputLayoutName[] = "IVertexShader::InputLayout";
	_inputLayout->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(inputLayoutName) - 1, inputLayoutName);
#endif

	if (FAILED(r)) throw Exception("Failed to create the input layout!");
#endif
}

IVertexShader::IVertexShader(GraphicsDevice*Device, std::span<InputLayoutElement> inputLayout, const char *shaderSourceCode, const char *vsEntry, ShaderFeatureLevel fl):
	IShader(Device, shaderSourceCode, vsEntry, fl)
{
	_compileShader(shaderSourceCode, _determineTarget());
	_createShader();
	_generateInputLayout(inputLayout);
}

IVertexShader::IVertexShader(GraphicsDevice*Device, std::span<InputLayoutElement> inputLayout, const std::filesystem::path &path, const char *vsEntry, ShaderFeatureLevel fl):
	IShader(Device, path, vsEntry, fl)
{
	_compileShaderFromFile(path.string().c_str(), _determineTarget());
	_createShader();
	_generateInputLayout(inputLayout);
}

void IVertexShader::SetTexture(unsigned index, Texture2D *texture)
{
#ifdef USING_DX11
	_device->_context->VSSetShaderResources(index, 1, texture->_resourceView.GetAddressOf());
#endif
}

void IVertexShader::SetSampler(unsigned index, SamplerState *samplerState)
{
#ifdef USING_DX11
	_device->_context->VSSetSamplers(index, 1, samplerState->_samplerState.GetAddressOf());
#endif
}

void IVertexShader::SetShader()
{
#ifdef  USING_DX11
	unsigned i;
	auto validConstantBuffers = this->_validConstantBuffers(i);
	_device->_context->VSSetConstantBuffers(0, i, validConstantBuffers.data());

	_device->_context->IASetInputLayout(_inputLayout.Get());
	_device->_context->VSSetShader(_shader.Get(), nullptr, 0);
#endif //  USING_DX11

}

void* IVertexShader::GetHandle() const noexcept
{
#ifdef USING_DX11
	return static_cast<void*>(_shader.Get());
#endif
}
