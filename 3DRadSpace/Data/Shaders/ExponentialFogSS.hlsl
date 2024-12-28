//Screen space exponential fog
// Vertex shader is used from PostProcessBase.hlsl

//Texture1 - backbuffer rendertarget.
//Texture2 - depth buffer.
Texture2D Main : register(t0);
Texture2D Depth : register(t1);
SamplerState TextureSampler : register(s0);

cbuffer FogInfo : register(b0)
{
    float4 FogColor;
    float Density;
}

struct Vertex
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD;
};

float4 PS_Main(Vertex v) : SV_TARGET
{
    return Main.Sample(TextureSampler, v.UV) + //color component
    FogColor * (1 / exp(Density * Depth.Sample(TextureSampler, v.UV))); //linear fog component
}