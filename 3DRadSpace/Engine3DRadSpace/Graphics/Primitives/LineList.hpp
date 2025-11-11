#pragma once
#include "IPrimitive.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Represents a 3D primitive composed of multiple lines.
	/// </summary>
	/// <remarks>
	/// Unline the Box type, it is considered okay to use multiple instances of this but each instance should have a different list of lines.
	/// Copy constructors are removed, each instance should be unique.
	/// Move constructors are preserved for container usage.
	/// The topology used for drawing lines is a list of lines, thus duplicate coordinates could be needed.
	/// One could prefer drawing a wireframe mesh, but changing the rasterizer state.
	/// </remarks>
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT LineList : public IPrimitive
	{
		std::unique_ptr<IRasterizerState> _lineRasterizer;
		std::unique_ptr<IRasterizerState> _oldRasterizerState;
	protected:
		void _swapRasterizer();
		void _restoreRasterizer();
	public:
		/// <summary>
		/// Constructs a line mesh, from the specified array of vertices.
		/// </summary>
		/// <param name="device">Graphics device.</param>
		/// <param name="points">List of points.</param>
		LineList(IGraphicsDevice *device, std::span<VertexPositionColor> points);

		LineList(const LineList &) = delete;
		LineList(LineList &&) noexcept = default;

		LineList &operator=(const LineList &) = delete;
		LineList &operator=(LineList &&) noexcept = default;

		/// <summary>
		/// Rasterizer state used to render lines.
		/// </summary>
		/// <returns>rasterizer state handle</returns>
		IRasterizerState* GetLineRasterizer() const noexcept;

		/// <summary>
		/// Draws this primitive shape.
		/// </summary>
		virtual void Draw3D() override;
	};
}