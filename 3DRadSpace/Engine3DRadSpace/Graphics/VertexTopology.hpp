/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/VertexTopology.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once

namespace Engine3DRadSpace::Graphics
{
    enum class VertexTopology
    {
        Undefined = 0,
        PointList,
        LineList,
        LineStrip,
        TriangleList,
        TriangleStrip,
        LineList_Adj,
        LineStrip_Adj,
        TriangleList_Adj,
        TriangleStrip_Adj,
	};	 
}