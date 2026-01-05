#pragma once

namespace Engine3DRadSpace::Graphics
{
	enum class RasterizerFillMode : unsigned char
	{
		/// <summary>
		/// Triangles will be drawn in wireframe.
		/// </summary>
		Wireframe = 2,
		/// <summary>
		/// Triangles will be fully drawn.
		/// </summary>
		Solid = 3
	};
}