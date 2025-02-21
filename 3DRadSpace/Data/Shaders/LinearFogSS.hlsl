//Screen space fog
// Vertex shader is used from PostProcessBase.hlsl
#include <PostProcessBase.hlsl>

//Texture1 - backbuffer rendertarget.
//Texture2 - depth buffer.
Texture2D Main : register(t0);
Texture2D Depth : register(t1);
SamplerState TextureSampler : register(s0);

cbuffer FogInfo : register(b0)
{
    float FogBegin;
    float FogEnd;
    float4 FogColor;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    return Main.Sample(TextureSampler, v.UV) * float4(1,0,0,1) + //color component
    FogColor * saturate((FogEnd - Depth.Sample(TextureSampler, v.UV) / (FogEnd - FogBegin))); //linear fog component
}