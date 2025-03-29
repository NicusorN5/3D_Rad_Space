#include "Texture2D.hpp"

#ifdef USING_DX11
#include <directxtk/WICTextureLoader.h>
#include <directxtk/DDSTextureLoader.h>
#include <Windows.h>
#include <directxtk/ScreenGrab.h>
#include <wincodec.h>
#endif // USING_DX11
#include "../Logging/Exception.hpp"
#include "../Logging/AssetLoadingError.hpp"
#include "../Internal/AssetUUIDReader.hpp"
#include "../GraphicsDevice.hpp"
#include "RenderTarget.hpp"
#include "../Content/ShaderManager.hpp"
#include "Shaders\SpriteShader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;

Texture2D::Texture2D(GraphicsDevice* device, const std::filesystem::path &path):
	_device(device)
{
	auto filename = path.wstring();
#ifdef USING_DX11
	ID3D11Resource** resource = reinterpret_cast<ID3D11Resource**>(_texture.GetAddressOf());

	HRESULT r = DirectX::CreateWICTextureFromFileEx(
		device->_device.Get(),
		device->_context.Get(),
		filename.c_str(),
		0u,
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		D3D11_CPU_ACCESS_WRITE,
		0,
		DirectX::DX11::WIC_LOADER_FORCE_SRGB,
		resource,
		_resourceView.GetAddressOf()
	);
	if (FAILED(r))
	{
		r = DirectX::CreateDDSTextureFromFileEx(
			device->_device.Get(),
			device->_context.Get(),
			filename.c_str(),
			0,
			D3D11_USAGE_DEFAULT,
			D3D11_BIND_SHADER_RESOURCE,
			D3D11_CPU_ACCESS_WRITE,
			0,
			DirectX::DX11::DDS_LOADER_FLAGS::DDS_LOADER_FORCE_SRGB,
			resource,
			_resourceView.GetAddressOf()
		);
	}

	if(FAILED(r))
	{
		char mbPath[_MAX_PATH]{};
		WideCharToMultiByte(CP_ACP, 0, filename.c_str(), int(filename.length()), mbPath, _MAX_PATH, nullptr, nullptr);
		throw AssetLoadingError(Tag<Texture2D>{}, mbPath, std::system_category().message(r));
	}

	_retrieveSize();
#endif
}

Texture2D::Texture2D(GraphicsDevice *device, std::span<Color> colors, unsigned x, unsigned y):
	_device(device),
	_width(x),
	_height(y)
{
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC tDesc{};
	tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	tDesc.Height = y;
	tDesc.Width = x;
	tDesc.Usage = D3D11_USAGE_DYNAMIC;
	tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tDesc.ArraySize = 1;
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;
	tDesc.MipLevels = 1;

	D3D11_SUBRESOURCE_DATA textureData{};
	textureData.pSysMem = &colors[0];
	textureData.SysMemPitch = sizeof(Color) * x;

	HRESULT r = device->_device->CreateTexture2D(&tDesc, &textureData, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!" + std::system_category().message(r));

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view! " + std::system_category().message(r));
#endif
	_debugInfoTX2D();
}

Texture2D::Texture2D(GraphicsDevice* device, void* buffer, unsigned x, unsigned y, PixelFormat format):
	_device(device),
	_width(x),
	_height(y)
{
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC tDesc{};
	tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tDesc.Format = _getTextureFormat(format);
	tDesc.Height = y;
	tDesc.Width = x;
	tDesc.Usage = D3D11_USAGE_DYNAMIC;
	tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tDesc.ArraySize = 1;
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;
	tDesc.MipLevels = 1;

	D3D11_SUBRESOURCE_DATA textureData{};
	textureData.pSysMem = buffer;
	textureData.SysMemPitch = sizeof(Color) * x;

	HRESULT r = device->_device->CreateTexture2D(&tDesc, &textureData, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!" + std::system_category().message(r));

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!" + std::system_category().message(r));
#endif
	_debugInfoTX2D();
}

Texture2D::Texture2D(GraphicsDevice* device, Color* colors, unsigned x, unsigned y):
	_device(device),
	_width(x),
	_height(y)
{
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = x;
	desc.Height = y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = colors;
	data.SysMemPitch = sizeof(Color) * x;

	HRESULT r = device->_device->CreateTexture2D(&desc, &data, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!" + std::system_category().message(r));

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!" + std::system_category().message(r));
#endif
	_debugInfoTX2D();
}

Texture2D::Texture2D(GraphicsDevice* device,const uint8_t* imageBuffer, size_t size):
	_device(device)
{
#ifdef USING_DX11
	auto resource = reinterpret_cast<ID3D11Resource**>(_texture.GetAddressOf());

	HRESULT r = DirectX::CreateWICTextureFromMemory(
		device->_device.Get(),
		device->_context.Get(),
		imageBuffer,
		size,
		resource,
		_resourceView.GetAddressOf()
	);
	if (FAILED(r))
	{
		r = DirectX::CreateWICTextureFromMemory(
			device->_device.Get(),
			device->_context.Get(),
			imageBuffer,
			size,
			resource,
			_resourceView.GetAddressOf()
		);
	}
	if (FAILED(r)) throw Exception("Failed to create texture from memory!" + std::system_category().message(r));

	_retrieveSize();
#endif
}

Texture2D::Texture2D(GraphicsDevice *device, unsigned x, unsigned y, PixelFormat format):
	_device(device),
	_width(x),
	_height(y)
{
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = x;
	desc.Height = y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = _getTextureFormat(format);

	HRESULT r = device->_device->CreateTexture2D(&desc, nullptr, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!" + std::system_category().message(r));

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!" + std::system_category().message(r));
#endif
	_debugInfoTX2D();
}

void Texture2D::_debugInfoTX2D()
{
#ifdef _DEBUG
#ifdef USING_DX11
	const char textureName[] = "Texture2D::_texture";
	_texture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureName) - 1, textureName);

	const char resourceViewName[] = "Texture2D::_resourceView";
	_resourceView->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(resourceViewName) - 1, resourceViewName);
#endif
#endif
}

void Texture2D::_debugInfoRT()
{
#ifdef _DEBUG
#ifdef USING_DX11
	const char textureName[] = "RenderTarget(Texture2D)::_texture";
	_texture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureName) - 1, textureName);

	const char resourceViewName[] = "RenderTarget(Texture2D)::_resourceView";
	_resourceView->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(resourceViewName) - 1, resourceViewName);
#endif
#endif
}

void Texture2D::_retrieveSize()
{
#ifdef  USING_DX11
	//Retrieve the image size
	D3D11_TEXTURE2D_DESC desc;
	_texture->GetDesc(&desc);

	_width = desc.Width;
	_height = desc.Height;
	_format = _getTextureFormatFromDX(desc.Format);
#endif //  USING_DX11
}

#ifdef  USING_DX11
DXGI_FORMAT Texture2D::_getTextureFormat(PixelFormat format)
{
	switch (format)
	{
		case PixelFormat::R32G32B32A32_Typeless: return DXGI_FORMAT_R32G32B32A32_TYPELESS;
		case PixelFormat::R32G32B32A32_Float: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case PixelFormat::R32G32B32A32_UnsignedInt: return DXGI_FORMAT_R32G32B32A32_UINT;
		case PixelFormat::R32G32B32A32_SignedInt: return DXGI_FORMAT_R32G32B32A32_SINT;

		case PixelFormat::R32G32B32_Typeless: return DXGI_FORMAT_R32G32B32_TYPELESS;
		case PixelFormat::R32G32B32_Float: return DXGI_FORMAT_R32G32B32_FLOAT;
		case PixelFormat::R32G32B32_UnsignedInt: return DXGI_FORMAT_R32G32B32_UINT;
		case PixelFormat::R32G32B32_SignedInt: return DXGI_FORMAT_R32G32B32_SINT;

		case PixelFormat::R16G16B16A16_Typeless: return DXGI_FORMAT_R16G16B16A16_TYPELESS;
		case PixelFormat::R16G16B16A16_Float: return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case PixelFormat::R16G16B16A16_UnsignedNormalized: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case PixelFormat::R16G16B16A16_UnsignedInt: return DXGI_FORMAT_R16G16B16A16_UINT;
		case PixelFormat::R16G16B16A16_SignedNormalized: return DXGI_FORMAT_R16G16B16A16_SNORM;
		case PixelFormat::R16G16B16A16_SignedInt: return DXGI_FORMAT_R16G16B16A16_SINT;

		case PixelFormat::R32G32_Typeless: return DXGI_FORMAT_R32G32_TYPELESS;
		case PixelFormat::R32G32_Float: return DXGI_FORMAT_R32G32_FLOAT;
		case PixelFormat::R32G32_UnsignedInt: return DXGI_FORMAT_R32G32_UINT;
		case PixelFormat::R32G32_SignedInt: return DXGI_FORMAT_R32G32_SINT;

		case PixelFormat::R32G8X24_Typeless: return DXGI_FORMAT_R32G8X24_TYPELESS;

		case PixelFormat::D32_Float_S8X24_UnsignedInt: return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		case PixelFormat::R32_Float_X8X24_Typeless: return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
		case PixelFormat::X32_Typeless_G8X24_UnsignedInt: return DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;

		case PixelFormat::R10G10B10A2_Typeless: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case PixelFormat::R10G10B10A2_UnsignedNormalized: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case PixelFormat::R10G10B10A2_UnsignedInt: return DXGI_FORMAT_R10G10B10A2_UINT;
		case PixelFormat::R11G11B10_Float: return DXGI_FORMAT_R11G11B10_FLOAT;

		case PixelFormat::R8G8B8A8_Typeless: return DXGI_FORMAT_R8G8B8A8_TYPELESS;
		case PixelFormat::R8G8B8A8_UnsignedNormalized: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case PixelFormat::R8G8B8A8_UnsignedNormalized_SRGB: return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case PixelFormat::R8G8B8A8_UnsignedInt: return DXGI_FORMAT_R8G8B8A8_UINT;
		case PixelFormat::R8G8B8A8_SignedNormalized: return DXGI_FORMAT_R8G8B8A8_SNORM;
		case PixelFormat::R8G8B8A8_SignedInt: return DXGI_FORMAT_R8G8B8A8_SINT;
			
		case PixelFormat::R16G16_Typeless: return DXGI_FORMAT_R16G16_TYPELESS;
		case PixelFormat::R16G16_Float: return DXGI_FORMAT_R16G16_FLOAT;
		case PixelFormat::R16G16_UnsignedNormalized: return DXGI_FORMAT_R16G16_UNORM;
		case PixelFormat::R16G16_UnsignedInt: return DXGI_FORMAT_R16G16_UINT;
		case PixelFormat::R16G16_SignedNormalized: return DXGI_FORMAT_R16G16_SNORM;
		case PixelFormat::R16G16_SignedInt: return DXGI_FORMAT_R16G16_SINT;

		case PixelFormat::R32_Typeless: return DXGI_FORMAT_R32_TYPELESS;
		case PixelFormat::D32_Float: return DXGI_FORMAT_D32_FLOAT;
		case PixelFormat::R32_Float: return DXGI_FORMAT_R32_FLOAT;
		case PixelFormat::R32_UnsignedInt: return DXGI_FORMAT_R32_UINT;
		case PixelFormat::R32_SignedInt: return DXGI_FORMAT_R32_SINT;
		
		case PixelFormat::R24G8_Typeless: return DXGI_FORMAT_R24G8_TYPELESS;
		case PixelFormat::D24_UnsignedNormalized_S8_UnsignedInt: return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case PixelFormat::R24_UnsignedNormalized_X8_Typeless: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		case PixelFormat::X24_Typeless_G8_UnsignedInt: return DXGI_FORMAT_X24_TYPELESS_G8_UINT;

		case PixelFormat::R8G8_Typeless: return DXGI_FORMAT_R8G8_TYPELESS;
		case PixelFormat::R8G8_UnsignedNormalized: return DXGI_FORMAT_R8G8_UNORM;
		case PixelFormat::R8G8_UnsignedInt: return DXGI_FORMAT_R8G8_UINT;
		case PixelFormat::R8G8_SignedNormalized: return DXGI_FORMAT_R8G8_SNORM;
		case PixelFormat::R8G8_SignedInt: return DXGI_FORMAT_R8G8_SINT;
			
		case PixelFormat::R16_Typeless: return DXGI_FORMAT_R16_TYPELESS;
		case PixelFormat::R16_Float: return DXGI_FORMAT_R16_FLOAT;
		case PixelFormat::D16_UnsignedNormalized: return DXGI_FORMAT_D16_UNORM;
		case PixelFormat::R16_UnsignedNormalized: return DXGI_FORMAT_R16_UNORM;
		case PixelFormat::R16_UnsignedInt: return DXGI_FORMAT_R16_UINT;
		case PixelFormat::R16_SignedNormalized: return DXGI_FORMAT_R16_SNORM;
		case PixelFormat::R16_SignedInt: return DXGI_FORMAT_R16_SINT;
			
		case PixelFormat::R8_Typeless: return DXGI_FORMAT_R8_TYPELESS;
		case PixelFormat::R8_UnsignedNormalized: return DXGI_FORMAT_R8_UNORM;
		case PixelFormat::R8_UnsignedInt: return DXGI_FORMAT_R8_UINT;
		case PixelFormat::R8_SignedNormalized: return DXGI_FORMAT_R8_SNORM;
		case PixelFormat::R8_SignedInt: return DXGI_FORMAT_R8_SINT;
		case PixelFormat::A8_UnsignedNormalized: return DXGI_FORMAT_A8_UNORM;

		case PixelFormat::R1_UnsignedNormalized: return DXGI_FORMAT_R1_UNORM;
		case PixelFormat::R9G9B9E5_SHAREDEXP: return  DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
		case PixelFormat::R8G8_B8G8_UnsignedNormalized: return DXGI_FORMAT_R8G8_B8G8_UNORM;
		case PixelFormat::G8R8_G8B8_UnsignedNormalized: return DXGI_FORMAT_G8R8_G8B8_UNORM;
			
		case PixelFormat::BC1_Typeless: return DXGI_FORMAT_BC1_TYPELESS;
		case PixelFormat::BC1_UnsignedNormalized: return DXGI_FORMAT_BC1_UNORM;
		case PixelFormat::BC1_UnsignedNormalized_SRGB: return DXGI_FORMAT_BC1_UNORM_SRGB;
			
		case PixelFormat::BC2_Typeless: return DXGI_FORMAT_BC2_TYPELESS;
		case PixelFormat::BC2_UnsignedNormalized: return DXGI_FORMAT_BC2_UNORM;
		case PixelFormat::BC2_UnsignedNormalized_SRGB: return DXGI_FORMAT_BC2_UNORM_SRGB;

		case PixelFormat::BC3_Typeless: return DXGI_FORMAT_BC3_TYPELESS;
		case PixelFormat::BC3_UnsignedNormalized: return DXGI_FORMAT_BC3_UNORM;
		case PixelFormat::BC3_UnsignedNormalized_SRGB: return DXGI_FORMAT_BC3_UNORM_SRGB;
			
		case PixelFormat::BC4_Typeless: return DXGI_FORMAT_BC4_TYPELESS;
		case PixelFormat::BC4_UnsignedNormalized: return DXGI_FORMAT_BC4_UNORM;
		case PixelFormat::BC4_SignedNormalized: return DXGI_FORMAT_BC4_SNORM;

		case PixelFormat::BC5_Typeless: return DXGI_FORMAT_BC5_TYPELESS;
		case PixelFormat::BC5_UnsignedNormalized: return DXGI_FORMAT_BC5_UNORM;
		case PixelFormat::BC5_SignedNormalized: return DXGI_FORMAT_BC5_SNORM;

		case PixelFormat::B5G6R5_UnsignedNormalized: return DXGI_FORMAT_B5G6R5_UNORM;
		case PixelFormat::B5G5R5A1_UnsignedNormalized: return DXGI_FORMAT_B5G5R5A1_UNORM;

		case PixelFormat::B8G8R8A8_UnsignedNormalized: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case PixelFormat::B8G8R8X8_UnsignedNormalized: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case PixelFormat::R10G10B10_XR_BIAS_A2_UnsignedNormalized: return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;

		case PixelFormat::B8G8R8A8_Typeless: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case PixelFormat::B8G8R8A8_UnsignedNormalized_SRGB: return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		case PixelFormat::B8G8R8X8_Typeless: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case PixelFormat::B8G8R8X8_UnsignedNormalized_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
			
		case PixelFormat::BC6H_Typeless: return DXGI_FORMAT_BC6H_TYPELESS;
		case PixelFormat::BC6H_UF16: return DXGI_FORMAT_BC6H_UF16;
		case PixelFormat::BC6H_SF16: return DXGI_FORMAT_BC6H_SF16;

		case PixelFormat::BC7_Typeless: return DXGI_FORMAT_BC7_TYPELESS;
		case PixelFormat::BC7_UnsignedNormalized: return DXGI_FORMAT_BC7_UNORM;
		case PixelFormat::BC7_UnsignedNormalized_SRGB: return DXGI_FORMAT_BC7_UNORM_SRGB;
		case PixelFormat::AYUV: return DXGI_FORMAT_AYUV;
			
		case PixelFormat::Y410: return DXGI_FORMAT_Y410;
		case PixelFormat::Y416: return DXGI_FORMAT_Y416;
		case PixelFormat::NV12: return DXGI_FORMAT_NV12;
		case PixelFormat::P010: return DXGI_FORMAT_P010;
		case PixelFormat::P016: return DXGI_FORMAT_P016;
		case PixelFormat::Video_YUV_420_Opaque: return DXGI_FORMAT_420_OPAQUE;
		
		case PixelFormat::YUY2: return DXGI_FORMAT_YUY2;
		case PixelFormat::Y210: return DXGI_FORMAT_Y210;
		case PixelFormat::Y216: return DXGI_FORMAT_Y216;
		case PixelFormat::NV11: return DXGI_FORMAT_NV11;
		case PixelFormat::AI44: return DXGI_FORMAT_AI44;
		case PixelFormat::IA44: return DXGI_FORMAT_IA44;
		case PixelFormat::P8: return DXGI_FORMAT_P8;
		case PixelFormat::A8P8: return DXGI_FORMAT_A8P8;
		case PixelFormat::B4G4R4A4_UnsignedNormalized: return DXGI_FORMAT_B4G4R4A4_UNORM;

		case PixelFormat::P208: return DXGI_FORMAT_P208;
		case PixelFormat::V208: return DXGI_FORMAT_V208;
		case PixelFormat::V408: return DXGI_FORMAT_V408;
	default:
		return DXGI_FORMAT_UNKNOWN;
	}
}

PixelFormat Texture2D::_getTextureFormatFromDX(DXGI_FORMAT format)
{
	switch (format)
	{
		case DXGI_FORMAT_R32G32B32A32_TYPELESS: return PixelFormat::R32G32B32A32_Typeless;
		case DXGI_FORMAT_R32G32B32A32_FLOAT: return PixelFormat::R32G32B32A32_Float;
		case DXGI_FORMAT_R32G32B32A32_UINT: return PixelFormat::R32G32B32A32_UnsignedInt;
		case DXGI_FORMAT_R32G32B32A32_SINT: return PixelFormat::R32G32B32A32_SignedInt;

		case DXGI_FORMAT_R32G32B32_TYPELESS: return PixelFormat::R32G32B32_Typeless;
		case DXGI_FORMAT_R32G32B32_FLOAT: return PixelFormat::R32G32B32_Float;
		case DXGI_FORMAT_R32G32B32_UINT: return PixelFormat::R32G32B32_UnsignedInt;
		case DXGI_FORMAT_R32G32B32_SINT: return PixelFormat::R32G32B32_SignedInt;

		case DXGI_FORMAT_R16G16B16A16_TYPELESS: return PixelFormat::R16G16B16A16_Typeless;
		case DXGI_FORMAT_R16G16B16A16_FLOAT: return PixelFormat::R16G16B16A16_Float;
		case DXGI_FORMAT_R16G16B16A16_UNORM: return PixelFormat::R16G16B16A16_UnsignedNormalized;
		case DXGI_FORMAT_R16G16B16A16_UINT: return PixelFormat::R16G16B16A16_UnsignedInt;
		case DXGI_FORMAT_R16G16B16A16_SNORM: return PixelFormat::R16G16B16A16_SignedNormalized;
		case DXGI_FORMAT_R16G16B16A16_SINT: return PixelFormat::R16G16B16A16_SignedInt;

		case DXGI_FORMAT_R32G32_TYPELESS: return PixelFormat::R32G32_Typeless;
		case DXGI_FORMAT_R32G32_FLOAT: return PixelFormat::R32G32_Float;
		case DXGI_FORMAT_R32G32_UINT: return PixelFormat::R32G32_UnsignedInt;
		case DXGI_FORMAT_R32G32_SINT: return PixelFormat::R32G32_SignedInt;

		case DXGI_FORMAT_R32G8X24_TYPELESS: return PixelFormat::R32G8X24_Typeless;

		case DXGI_FORMAT_D32_FLOAT_S8X24_UINT: return PixelFormat::D32_Float_S8X24_UnsignedInt;
		case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS: return PixelFormat::R32_Float_X8X24_Typeless;
		case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT: return PixelFormat::X32_Typeless_G8X24_UnsignedInt;

		case DXGI_FORMAT_R10G10B10A2_TYPELESS: return PixelFormat::R10G10B10A2_Typeless;
		case DXGI_FORMAT_R10G10B10A2_UNORM: return PixelFormat::R10G10B10A2_UnsignedNormalized;
		case DXGI_FORMAT_R10G10B10A2_UINT: return PixelFormat::R10G10B10A2_UnsignedInt;
		case DXGI_FORMAT_R11G11B10_FLOAT: return PixelFormat::R11G11B10_Float;

		case DXGI_FORMAT_R8G8B8A8_TYPELESS: return PixelFormat::R8G8B8A8_Typeless;
		case DXGI_FORMAT_R8G8B8A8_UNORM: return PixelFormat::R8G8B8A8_UnsignedNormalized;
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB : return PixelFormat::R8G8B8A8_UnsignedNormalized_SRGB;
		case DXGI_FORMAT_R8G8B8A8_UINT: return PixelFormat::R8G8B8A8_UnsignedInt;
		case DXGI_FORMAT_R8G8B8A8_SNORM: return PixelFormat::R8G8B8A8_SignedNormalized;
		case DXGI_FORMAT_R8G8B8A8_SINT: return PixelFormat::R8G8B8A8_SignedInt;
			
		case DXGI_FORMAT_R16G16_TYPELESS: return PixelFormat::R16G16_Typeless;
		case DXGI_FORMAT_R16G16_FLOAT: return PixelFormat::R16G16_Float;
		case DXGI_FORMAT_R16G16_UNORM: return PixelFormat::R16G16_UnsignedNormalized;
		case DXGI_FORMAT_R16G16_UINT: return PixelFormat::R16G16_UnsignedInt;
		case DXGI_FORMAT_R16G16_SNORM: return PixelFormat::R16G16_SignedNormalized;
		case DXGI_FORMAT_R16G16_SINT: return PixelFormat::R16G16_SignedInt;

		case DXGI_FORMAT_R32_TYPELESS: return PixelFormat::R32_Typeless;
		case DXGI_FORMAT_D32_FLOAT: return PixelFormat::D32_Float;
		case DXGI_FORMAT_R32_FLOAT: return PixelFormat::R32_Float;
		case DXGI_FORMAT_R32_UINT: return PixelFormat::R32_UnsignedInt;
		case DXGI_FORMAT_R32_SINT: return PixelFormat::R32_SignedInt;
		
		case DXGI_FORMAT_R24G8_TYPELESS: return PixelFormat::R24G8_Typeless;
		case DXGI_FORMAT_D24_UNORM_S8_UINT: return PixelFormat::D24_UnsignedNormalized_S8_UnsignedInt;
		case DXGI_FORMAT_R24_UNORM_X8_TYPELESS: return PixelFormat::R24_UnsignedNormalized_X8_Typeless;
		case DXGI_FORMAT_X24_TYPELESS_G8_UINT: return PixelFormat::X24_Typeless_G8_UnsignedInt;

		case DXGI_FORMAT_R8G8_TYPELESS: return PixelFormat::R8G8_Typeless;
		case DXGI_FORMAT_R8G8_UNORM: return PixelFormat::R8G8_UnsignedNormalized;
		case DXGI_FORMAT_R8G8_UINT: return PixelFormat::R8G8_UnsignedInt;
		case DXGI_FORMAT_R8G8_SNORM: return PixelFormat::R8G8_SignedNormalized;
		case DXGI_FORMAT_R8G8_SINT: return PixelFormat::R8G8_SignedInt;
			
		case DXGI_FORMAT_R16_TYPELESS: return PixelFormat::R16_Typeless;
		case DXGI_FORMAT_R16_FLOAT: return PixelFormat::R16_Float;
		case DXGI_FORMAT_D16_UNORM: return PixelFormat::D16_UnsignedNormalized;
		case DXGI_FORMAT_R16_UNORM: return PixelFormat::R16_UnsignedNormalized;
		case DXGI_FORMAT_R16_UINT: return PixelFormat::R16_UnsignedInt;
		case DXGI_FORMAT_R16_SNORM: return PixelFormat::R16_SignedNormalized;
		case DXGI_FORMAT_R16_SINT: return  PixelFormat::R16_SignedInt;
			
		case DXGI_FORMAT_R8_TYPELESS: return PixelFormat::R8_Typeless;
		case DXGI_FORMAT_R8_UNORM: return PixelFormat::R8_UnsignedNormalized;
		case DXGI_FORMAT_R8_UINT: return PixelFormat::R8_UnsignedInt;
		case DXGI_FORMAT_R8_SNORM: return PixelFormat::R8_SignedNormalized;
		case DXGI_FORMAT_R8_SINT: return PixelFormat::R8_SignedInt;
		case DXGI_FORMAT_A8_UNORM: return PixelFormat::A8_UnsignedNormalized;

		case DXGI_FORMAT_R1_UNORM: return PixelFormat::R1_UnsignedNormalized;
		case DXGI_FORMAT_R9G9B9E5_SHAREDEXP: return PixelFormat::R9G9B9E5_SHAREDEXP;
		case DXGI_FORMAT_R8G8_B8G8_UNORM: return PixelFormat::R8G8_B8G8_UnsignedNormalized;
		case DXGI_FORMAT_G8R8_G8B8_UNORM: return PixelFormat::G8R8_G8B8_UnsignedNormalized;
			
		case DXGI_FORMAT_BC1_TYPELESS: return PixelFormat::BC1_Typeless;
		case DXGI_FORMAT_BC1_UNORM: return PixelFormat::BC1_UnsignedNormalized;
		case DXGI_FORMAT_BC1_UNORM_SRGB: return PixelFormat::BC1_UnsignedNormalized_SRGB;
			
		case DXGI_FORMAT_BC2_TYPELESS: return PixelFormat::BC2_Typeless;
		case DXGI_FORMAT_BC2_UNORM: return PixelFormat::BC2_UnsignedNormalized;
		case DXGI_FORMAT_BC2_UNORM_SRGB: return PixelFormat::BC2_UnsignedNormalized_SRGB;

		case DXGI_FORMAT_BC3_TYPELESS: return PixelFormat::BC3_Typeless;
		case DXGI_FORMAT_BC3_UNORM: return PixelFormat::BC3_UnsignedNormalized;
		case DXGI_FORMAT_BC3_UNORM_SRGB: return PixelFormat::BC3_UnsignedNormalized_SRGB;
			
		case DXGI_FORMAT_BC4_TYPELESS: return PixelFormat::BC4_Typeless;
		case DXGI_FORMAT_BC4_UNORM: return PixelFormat::BC4_UnsignedNormalized;
		case DXGI_FORMAT_BC4_SNORM: return PixelFormat::BC4_SignedNormalized;

		case DXGI_FORMAT_BC5_TYPELESS: return PixelFormat::BC5_Typeless;
		case DXGI_FORMAT_BC5_UNORM: return PixelFormat::BC5_UnsignedNormalized;
		case DXGI_FORMAT_BC5_SNORM: return PixelFormat::BC5_SignedNormalized;

		case DXGI_FORMAT_B5G6R5_UNORM: return PixelFormat::B5G6R5_UnsignedNormalized;
		case DXGI_FORMAT_B5G5R5A1_UNORM: return PixelFormat::B5G5R5A1_UnsignedNormalized;

		case DXGI_FORMAT_B8G8R8A8_UNORM: return PixelFormat::B8G8R8A8_UnsignedNormalized;
		case DXGI_FORMAT_B8G8R8X8_UNORM: return PixelFormat::B8G8R8X8_UnsignedNormalized;
		case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM: return PixelFormat::R10G10B10_XR_BIAS_A2_UnsignedNormalized;

		case DXGI_FORMAT_B8G8R8A8_TYPELESS: return PixelFormat::B8G8R8A8_Typeless;
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB: return PixelFormat::B8G8R8A8_UnsignedNormalized_SRGB;
		case DXGI_FORMAT_B8G8R8X8_TYPELESS: return PixelFormat::B8G8R8X8_Typeless;
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB: return PixelFormat::B8G8R8X8_UnsignedNormalized_SRGB;
			
		case DXGI_FORMAT_BC6H_TYPELESS: return PixelFormat::BC6H_Typeless;
		case DXGI_FORMAT_BC6H_UF16: return PixelFormat::BC6H_UF16;
		case DXGI_FORMAT_BC6H_SF16: return PixelFormat::BC6H_SF16;

		case DXGI_FORMAT_BC7_TYPELESS: return PixelFormat::BC7_Typeless;
		case DXGI_FORMAT_BC7_UNORM: return PixelFormat::BC7_UnsignedNormalized;
		case DXGI_FORMAT_BC7_UNORM_SRGB: return PixelFormat::BC7_UnsignedNormalized_SRGB;
		case DXGI_FORMAT_AYUV: return PixelFormat::AYUV;
			
		case DXGI_FORMAT_Y410: return  PixelFormat::Y410;
		case DXGI_FORMAT_Y416: return PixelFormat::Y416;
		case DXGI_FORMAT_NV12: return PixelFormat::NV12;
		case DXGI_FORMAT_P010: return PixelFormat::P010;
		case DXGI_FORMAT_P016: return PixelFormat::P016;
		case DXGI_FORMAT_420_OPAQUE: return PixelFormat::Video_YUV_420_Opaque;
		
		case DXGI_FORMAT_YUY2: return PixelFormat::YUY2;
		case DXGI_FORMAT_Y210: return PixelFormat::Y210;
		case DXGI_FORMAT_Y216: return PixelFormat::Y216;
		case DXGI_FORMAT_NV11: return PixelFormat::NV11;
		case DXGI_FORMAT_AI44: return PixelFormat::AI44;
		case DXGI_FORMAT_IA44: return PixelFormat::IA44;
		case DXGI_FORMAT_P8: return PixelFormat::P8;
		case DXGI_FORMAT_A8P8: return PixelFormat::A8P8;
		case DXGI_FORMAT_B4G4R4A4_UNORM: return PixelFormat::B4G4R4A4_UnsignedNormalized;

		case DXGI_FORMAT_P208: return PixelFormat::P208;
		case DXGI_FORMAT_V208: return PixelFormat::V208;
		case DXGI_FORMAT_V408: return PixelFormat::V408;
	default:
		return PixelFormat::Unknown;
	}
}
#endif

Texture2D::Texture2D(GraphicsDevice *device, unsigned x, unsigned y, bool bindRenderTarget, PixelFormat format):
	_device(device),
	_width(x),
	_height(y)
{
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = x;
	desc.Height = y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | (bindRenderTarget ? D3D11_BIND_RENDER_TARGET : 0);
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = _getTextureFormat(format);

	HRESULT r = device->_device->CreateTexture2D(&desc, nullptr, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!" + std::system_category().message(r));

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!" + std::system_category().message(r));
#endif
	_debugInfoTX2D();
}

Texture2D::Texture2D(GraphicsDevice *device, std::monostate dummy, bool bindRenderTarget, PixelFormat format):
	_device(device)
{
	(void)dummy;
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = device->_resolution.X;
	desc.Height = device->_resolution.Y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | (bindRenderTarget ? D3D11_BIND_RENDER_TARGET : 0);
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = _getTextureFormat(format);

	HRESULT r = device->_device->CreateTexture2D(&desc, nullptr, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!" + std::system_category().message(r));

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!" + std::system_category().message(r));
#endif

	_width = device->_resolution.X;
	_height = device->_resolution.Y;
	_debugInfoRT();
}

Texture2D::Texture2D(Internal::AssetUUIDReader a):
	_device(nullptr),
	_width(0),
	_height(0),
	_format(PixelFormat::Unknown)
{
}

#ifdef USING_DX11
Texture2D::Texture2D(GraphicsDevice* device, Microsoft::WRL::ComPtr<ID3D11Texture2D>&& texture, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>&& resource) :
	_device(device),
	_texture(std::move(texture)),
	_resourceView(std::move(resource))
{
	_retrieveSize();
}

Texture2D::Texture2D(GraphicsDevice* device, std::monostate dummy, Microsoft::WRL::ComPtr<ID3D11Texture2D> && texture) :
	_device(device),
	_texture(std::move(texture)),
	_resourceView(nullptr)
{
	(void)dummy;
	_retrieveSize();
}
#endif

void Texture2D::SetColors(Color** colors, unsigned x, unsigned y)
{
#ifdef USING_DX11
	D3D11_MAPPED_SUBRESOURCE resource;

	HRESULT r = _device->_context->Map(_texture.Get(), 0, D3D11_MAP_WRITE, 0, &resource);
	if (FAILED(r)) throw Exception("Failed to map a texture!" + std::system_category().message(r));

	memcpy(resource.pData, colors, sizeof(Color) * x * y);
	_device->_context->Unmap(_texture.Get(), 0);
#endif
}

Texture2D Texture2D::CreateStaging(Texture2D* texture)
{
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC desc{};
	texture->_texture->GetDesc(&desc);

	//Keep a copy of the original texture desc.
	D3D11_TEXTURE2D_DESC resizedTextureDesc = desc;

	desc.Usage = D3D11_USAGE_STAGING;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.BindFlags = 0;
	desc.MipLevels = 0;
	desc.MiscFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> stagingTexture;
	HRESULT r = texture->_device->_device->CreateTexture2D(&desc, nullptr, &stagingTexture);
	if (FAILED(r)) throw Exception("Failed to create a staging texture!" + std::system_category().message(r));

	texture->_device->_context->CopyResource(stagingTexture.Get(), texture->_texture.Get());
#endif

	return Texture2D(texture->_device, std::monostate(), std::move(stagingTexture));
}

void Texture2D::Resize(unsigned newX, unsigned newY)
{
	RenderTarget rt(_device, newX, newY, _format);
	SamplerState ss(_device);

	_device->SetRenderTargetAndDisableDepth(&rt);
	_device->ClearRenderTarget(&rt,Colors::Black);

	auto effect = ShaderManager::LoadShader<Shaders::SpriteShader>(_device);
	effect->SetBasic();
	effect->SetTexture(this);
	effect->SetSamplerState(&ss);

	_device->SetScreenQuad();
	_device->DrawScreenQuad();

	_width = newX;
	_height = newY;

	_device->SetRenderTargetAndDepth(nullptr, nullptr);

	auto copy = static_cast<Texture2D*>(&rt);
	this->_texture = std::move(copy->_texture);
	this->_resourceView = std::move(copy->_resourceView);
}

void Texture2D::SaveToFile(const std::string &path)
{
#ifdef USING_DX11
	wchar_t wpath[_MAX_PATH]{};
	MultiByteToWideChar(CP_ACP, 0, path.c_str(), -1, wpath, _MAX_PATH);

	HRESULT r = DirectX::SaveWICTextureToFile(_device->_context.Get(), _texture.Get(), GUID_ContainerFormatPng, wpath, nullptr, nullptr, true);
	if(FAILED(r)) throw Exception("Failed to save file!" + std::system_category().message(r));
#endif
}

unsigned Texture2D::Width() const noexcept
{
	return _width;
}

unsigned Texture2D::Height() const noexcept
{
	return _height;
}

Point Texture2D::Size() const noexcept
{
	return Point(static_cast<int>(_width), static_cast<int>(_height));
}

Texture2D Texture2D::Clone()
{
#ifdef USING_DX11
	Microsoft::WRL::ComPtr<ID3D11Texture2D> copy = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv = nullptr;

	D3D11_TEXTURE2D_DESC desc{};
	this->_texture->GetDesc(&desc);

	HRESULT r = _device->_device->CreateTexture2D(&desc, nullptr, copy.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create staging texture" + std::system_category().message(r));

	_device->_context->CopyResource(copy.Get(), _texture.Get());

	r = _device->_device->CreateShaderResourceView(_texture.Get(), nullptr, srv.GetAddressOf()); //recreate the shader resource view for the new texture
	if (FAILED(r)) throw Exception("Failed to recreate the shader resource view!" + std::system_category().message(r));

	return Texture2D(_device, std::move(copy), std::move(srv));
#endif
}

std::pair<void*, size_t> Texture2D::BeginRead(unsigned resourceID)
{
#ifdef USING_DX11
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	HRESULT r = _device->_context->Map(_texture.Get(), resourceID, D3D11_MAP_READ, 0, &mappedResource);
	if(SUCCEEDED(r)) return { mappedResource.pData, mappedResource.RowPitch * _height };
	else return { nullptr, 0 };
#endif
}

void Texture2D::EndRead(unsigned resourceID)
{
#ifdef USING_DX11
	_device->_context->Unmap(_texture.Get(), 0);
#endif
}

void Texture2D::Copy(Texture2D* destination, Texture2D* source)
{
#ifdef USING_DX11
	destination->_device->_context->CopyResource(destination->_texture.Get(), source->_texture.Get());
#endif
}

void* Texture2D::TextureHandle() const noexcept
{
	return _texture.Get();
}

void* Texture2D::ResourceViewHandle() const noexcept
{
	return _resourceView.Get();
}

Reflection::UUID Texture2D::GetUUID() const noexcept
{
	// {5AAE5C7A-C0E7-405A-B6FD-03CF9E3E36CC}
	return { 0x5aae5c7a, 0xc0e7, 0x405a, { 0xb6, 0xfd, 0x3, 0xcf, 0x9e, 0x3e, 0x36, 0xcc } };
}

const char* Texture2D::FileExtension() const noexcept
{
	//Image formats supported by Texture2D::Texture2D, with support from DirectXTK.
	return  "Supported image formats (*.bmp;*.dib;.*jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png;*.dds)\0*.bmp;*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png;*.dds)\0"
			"Bitmap image(*.bmp;*.dib)\0*.bmp;*.dib\0"
			"Joint Photographic Experts Group (JPEG) image(*.jpg;*.jpeg)\0*.jpg;*.jpeg\0"
			"Graphics Interchange Format (GIF) image(*.gif)\0*.gif\0"
			"Tagged Image File Format (TIFF) image(*.tiff)\0*.tiff\0"
			"Portable Network Graphics (PNG) image(*.png)\0*.png\0"
			"DirectDraw Surface image(*.dds)\0*.dds\0"
			"All Files(*.*)\0*.*\0\0";
}
