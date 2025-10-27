#pragma once
#include "IPrimitive.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Represents a 3D primitive composed of a line strip.
	/// </summary>
	/// <remarks>
	/// Just like LineList, this swaps the rasterizer state when drawing.
	/// </remarks>
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT LineStrip : public IPrimitive
	{
		std::unique_ptr<IRasterizerState> _lineRasterizer;
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _oldRasterizerState;
#endif
	protected:
		void _swapRasterizer();
		void _restoreRasterizer();
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

		/// <summary>
		/// Gets the vertex buffer this instance was build with.
		/// </summary>
		/// <returns>Lines list</returns>
		IVertexBuffer* GetVertexBuffer() const noexcept;
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