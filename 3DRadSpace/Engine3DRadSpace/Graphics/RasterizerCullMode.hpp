#pragma once

namespace Engine3DRadSpace::Graphics
{
	enum class RasterizerCullMode : unsigned char
	{
		/// <summary>
		/// Always draw all triangles.
		/// </summary>
		None = 1,
		/// <summary>
		/// Do not draw font-facing trangles.
		/// </summary>
		CullFront = 2,
		/// <summary>
		/// Do not draw backfaces.
		/// </summary>
		CullBack = 3,
	};
}