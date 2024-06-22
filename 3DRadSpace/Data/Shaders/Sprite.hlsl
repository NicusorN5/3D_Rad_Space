Texture2D TextureModel : register(t0);
SamplerState TextureSampler : register(s0);

struct VertexIn
{
    float2 Position : POSITION;
    float2 UV : TEXCOORD;
	float4 TintColor : COLOR;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD;
	float4 TintColor : COLOR;
};

VertexOut VS_Main(VertexIn v)
{
    VertexOut r;
    r.Position = float4(v.Position.xy, 0, 1);
	r.UV = v.UV;
	r.TintColor = v.TintColor;
    return r;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    return v.TintColor * TextureModel.Sample(TextureSampler, v.UV);
}