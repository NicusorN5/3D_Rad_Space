//*************************************************************************************************
// HLSL Shader for all post processing effects. Must be included first in your post processing shaders.
// Notes: 
//  - Use VertexOut structure as input for the fragment shader function.
//  - PostProcessBase_Main is the vertex shader function, automatically used by the base class "Engine3DRadSpace::Graphics::Rendering::PostProcessEffect".
//  - It is not intended to use another vertex declaration as it is not needed for rendering post processing effects using screen quads.
//  - struct Vertex is only used as input for PostProcessBase_Main : Not necessary to use it in your shaders.
//*************************************************************************************************

struct Vertex
{
    float2 Position : POSITION;
    float2 UV : TEXCOORD;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD;
};

VertexOut PostProcessBase_Main(Vertex v)
{
    VertexOut r;
    r.Position = float4(v.Position.xy, 0, 1);
	r.UV = v.UV;
    return r;
}