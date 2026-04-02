#pragma once

enum class E3DRSP_VertexTopology
{
    E3DRSP_VertexTopology_Undefined = 0,
    E3DRSP_VertexTopology_PointList,
    E3DRSP_VertexTopology_LineList,
    E3DRSP_VertexTopology_LineStrip,
    E3DRSP_VertexTopology_TriangleList,
    E3DRSP_VertexTopology_TriangleStrip,
    E3DRSP_VertexTopology_LineList_Adj,
    E3DRSP_VertexTopology_LineStrip_Adj,
    E3DRSP_VertexTopology_TriangleList_Adj,
    E3DRSP_VertexTopology_TriangleStrip_Adj,
};