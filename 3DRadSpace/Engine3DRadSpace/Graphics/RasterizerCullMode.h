#pragma once

enum E3DRSP_RasterizerCullMode
{
	/// <summary>
	/// Always draw all triangles.
	/// </summary>
	E3DRSP_RasterizerCullMode_None = 1,
	/// <summary>
	/// Do not draw font-facing trangles.
	/// </summary>
	E3DRSP_RasterizerCullMode_CullFront = 2,
	/// <summary>
	/// Do not draw backfaces.
	/// </summary>
	E3DRSP_RasterizerCullMode_CullBack = 3,
};