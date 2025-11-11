#pragma once
#include "LineList.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Represents a 3D primitive composed of a line strip.
	/// </summary>
	/// <remarks>
	/// Just like LineList, this swaps the rasterizer state when drawing.
	/// </remarks>
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT LineStrip : public LineList
	{
	public:
		/// <summary>
		/// Constructs a line mesh, from the specified array of vertices.
		/// </summary>
		/// <param name="device">Graphics device.</param>
		/// <param name="points">List of points.</param>
		LineStrip(IGraphicsDevice *device, std::span<VertexPositionColor> points);

		LineStrip(const LineStrip &) = delete;
		LineStrip(LineStrip &&) noexcept = default;

		LineStrip &operator=(const LineStrip &) = delete;
		LineStrip &operator=(LineStrip &&) noexcept = default;
	};
}