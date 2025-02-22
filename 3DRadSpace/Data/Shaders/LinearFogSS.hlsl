//Screen space fog
// Vertex shader is used from PostProcessBase.hlsl
#include <PostProcessBase.hlsl>

//Texture1 - backbuffer rendertarget.
Texture2D Main : register(t0);
//Texture2 - depth buffer.
Texture2D Depth : register(t1);
SamplerState TextureSampler : register(s0);

cbuffer FogInfo : register(b0)
{
    float FogBegin;
    float FogEnd;
    float near;
    float far;
    float4 FogColor;
}

float normalize_depth(float depth)
{
	return (2.0f * near) / (far + near - depth * (far - near));
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    float linear_depth = normalize_depth(Depth.Sample(TextureSampler, v.UV).r);
    float fog_density = saturate(linear_depth / (FogEnd - FogBegin) - FogBegin);
    
    float4 fog = FogColor * fog_density;
    float4 main = Main.Sample(TextureSampler, v.UV) * (1 - fog_density);
    return main + fog;
}