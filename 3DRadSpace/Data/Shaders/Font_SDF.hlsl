cbuffer Data : register(b0)
{
    float4 TintColor;
    bool FlipU;
    bool FlipV;
    float Smoothing; //1.0/16.0
}

Texture2D TextureModel : register(t0);
SamplerState TextureSampler : register(s0);

struct VertexIn
{
    float2 Position : POSITION;
    float2 UV : TEXCOORD;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD;
};

VertexOut VS_Main(VertexIn v)
{
    VertexOut r;
    r.Position = float4(v.Position.xy, 0, 1);
    
    //flip X
    if (FlipU)
        r.UV.x = 1 - v.UV.x;
    else
        r.UV.x = v.UV.x;
    
    // flip X
    if(FlipV)
        r.UV.y = 1 - v.UV.y;
    else 
        r.UV.y = v.UV.y;
    return r;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    //https://libgdx.com/wiki/graphics/2d/fonts/distance-field-fonts
    float distance = TextureModel.Sample(TextureSampler, v.UV).a;
    float alpha = smoothstep(0.5 - Smoothing, 0.5 + Smoothing, distance);
    
    return float4(TintColor.rbg, alpha * TintColor.a);
}