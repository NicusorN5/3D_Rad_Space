cbuffer AllData : register(b0)
{
    row_major matrix matWorldViewProj;
    row_major matrix matWorld;
    row_major matrix matWorldInverseTranspose;
    float4 LightColor;
    float4 AmbientColor;
    float3 LightDirection;
    float Intensity;
}

cbuffer ShadowData : register(b1)
{
    row_major matrix matLightViewProj;
    float ShadowBias;
    float ShadowIntensity;
    float2 ShadowTexelSize; // 1 / shadow map resolution, for PCF tap offsets
}

Texture2D shadowMap : register(t0);
SamplerState shadowSampler : register(s0);

struct VertexIn
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
    float4 Color : COLOR;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float3 Normal : NORMAL;
    float4 Color : COLOR;
    float4 LightSpacePos : TEXCOORD0;
};

VertexOut VS_Main(VertexIn v)
{
    VertexOut r;
    r.Position = mul(float4(v.Position.xyz, 1), matWorldViewProj);
    r.Normal = mul(float4(v.Normal.xyz, 0), matWorldInverseTranspose).xyz;
    r.Color = v.Color;

    float4 worldPos = mul(float4(v.Position.xyz, 1), matWorld);
    r.LightSpacePos = mul(worldPos, matLightViewProj);
    return r;
}

// Returns the shadow attenuation factor in [ShadowIntensity, 1.0] using 3x3 PCF for soft edges.
float ComputeShadow(float4 lightSpacePos)
{
    float3 proj = lightSpacePos.xyz / lightSpacePos.w;

    // NDC [-1,1] -> texture UV [0,1], flipping Y for D3D.
    float2 uv = proj.xy * float2(0.5, -0.5) + 0.5;

    // Outside the shadow map (or beyond the far plane) means lit.
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0 || proj.z > 1.0 || proj.z < 0.0)
        return 1.0;

    float currentDepth = proj.z;

    // 3x3 percentage-closer filtering: average the binary occlusion tests of neighbouring texels.
    float sum = 0.0;
    [unroll]
    for (int x = -1; x <= 1; x++)
    {
        [unroll]
        for (int y = -1; y <= 1; y++)
        {
            float2 offset = float2(x, y) * ShadowTexelSize;
            float closestDepth = shadowMap.Sample(shadowSampler, uv + offset).r;
            sum += (currentDepth - ShadowBias > closestDepth) ? ShadowIntensity : 1.0;
        }
    }

    return sum / 9.0;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    float diffuse = max(0, dot(normalize(v.Normal), -LightDirection));
    float shadow = ComputeShadow(v.LightSpacePos);

    // Shadows attenuate only the direct light term; ambient stays.
    return v.Color * (AmbientColor + LightColor * Intensity * diffuse * shadow);
}
