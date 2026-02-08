#include "PixelFormat.hpp"

using namespace Engine3DRadSpace::Graphics;

DXGI_FORMAT Engine3DRadSpace::Graphics::DirectX11::PixelFormat_ToDX11(PixelFormat format)
{
	switch(format)
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

PixelFormat Engine3DRadSpace::Graphics::DirectX11::PixelFormat_FromDX11(DXGI_FORMAT format)
{
	switch(format)
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
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB: return PixelFormat::R8G8B8A8_UnsignedNormalized_SRGB;
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