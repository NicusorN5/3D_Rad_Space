#pragma once

namespace Engine3DRadSpace::Graphics
{
    /// <summary>
    /// Represents all texture pixel formats supported when creating a Texture2D.
    /// </summary>
    enum class PixelFormat : unsigned int
    {
        Unknown = 0,
        R32G32B32A32_Typeless,
        R32G32B32A32_Float,
        R32G32B32A32_UnsignedInt,
        R32G32B32A32_SignedInt,
        R32G32B32_Typeless,
        R32G32B32_Float,
        R32G32B32_UnsignedInt,
        R32G32B32_SignedInt,
        R16G16B16A16_Typeless,
        R16G16B16A16_Float,
        R16G16B16A16_UnsignedNormalized,
        R16G16B16A16_UnsignedInt,
        R16G16B16A16_SignedNormalized,
        R16G16B16A16_SignedInt,
        R32G32_Typeless,
        R32G32_Float,
        R32G32_UnsignedInt,
        R32G32_SignedInt,
        R32G8X24_Typeless,
        D32_Float_S8X24_UnsignedInt,
        R32_Float_X8X24_Typeless,
        X32_Typeless_G8X24_UnsignedInt,
        R10G10B10A2_Typeless,
        R10G10B10A2_UnsignedNormalized,
        R10G10B10A2_UnsignedInt,
        R11G11B10_Float,
        R8G8B8A8_Typeless,
        R8G8B8A8_UnsignedNormalized,
        R8G8B8A8_UnsignedNormalized_SRGB,
        R8G8B8A8_UnsignedInt,
        R8G8B8A8_SignedNormalized,
        R8G8B8A8_SignedInt,
        R16G16_Typeless,
        R16G16_Float,
        R16G16_UnsignedNormalized,
        R16G16_UnsignedInt,
        R16G16_SignedNormalized,
        R16G16_SignedInt,
        R32_Typeless,
        D32_Float,
        R32_Float,
        R32_UnsignedInt,
        R32_SignedInt,
        R24G8_Typeless,
        D24_UnsignedNormalized_S8_UnsignedInt,
        R24_UnsignedNormalized_X8_Typeless,
        X24_Typeless_G8_UnsignedInt,
        R8G8_Typeless,
        R8G8_UnsignedNormalized,
        R8G8_UnsignedInt,
        R8G8_SignedNormalized,
        R8G8_SignedInt,
        R16_Typeless,
        R16_Float,
        D16_UnsignedNormalized,
        R16_UnsignedNormalized,
        R16_UnsignedInt,
        R16_SignedNormalized,
        R16_SignedInt,
        R8_Typeless,
        R8_UnsignedNormalized,
        R8_UnsignedInt,
        R8_SignedNormalized,
        R8_SignedInt,
        A8_UnsignedNormalized,
        R1_UnsignedNormalized,
        R9G9B9E5_SHAREDEXP,
        R8G8_B8G8_UnsignedNormalized,
        G8R8_G8B8_UnsignedNormalized,
        BC1_Typeless,
        BC1_UnsignedNormalized,
        BC1_UnsignedNormalized_SRGB,
        BC2_Typeless,
        BC2_UnsignedNormalized,
        BC2_UnsignedNormalized_SRGB,
        BC3_Typeless,
        BC3_UnsignedNormalized,
        BC3_UnsignedNormalized_SRGB,
        BC4_Typeless,
        BC4_UnsignedNormalized,
        BC4_SignedNormalized,
        BC5_Typeless,
        BC5_UnsignedNormalized,
        BC5_SignedNormalized,
        B5G6R5_UnsignedNormalized,
        B5G5R5A1_UnsignedNormalized,
        B8G8R8A8_UnsignedNormalized,
        B8G8R8X8_UnsignedNormalized,
        R10G10B10_XR_BIAS_A2_UnsignedNormalized,
        B8G8R8A8_Typeless,
        B8G8R8A8_UnsignedNormalized_SRGB,
        B8G8R8X8_Typeless,
        B8G8R8X8_UnsignedNormalized_SRGB,
        BC6H_Typeless,
        BC6H_UF16,
        BC6H_SF16,
        BC7_Typeless,
        BC7_UnsignedNormalized,
        BC7_UnsignedNormalized_SRGB,
        AYUV,
        Y410,
        Y416,
        NV12,
        P010,
        P016,
        Video_YUV_420_Opaque,
        YUY2,
        Y210,
        Y216,
        NV11,
        AI44,
        IA44,
        P8,
        A8P8,
        B4G4R4A4_UnsignedNormalized,

        P208,
        V208,
        V408,
    };
}