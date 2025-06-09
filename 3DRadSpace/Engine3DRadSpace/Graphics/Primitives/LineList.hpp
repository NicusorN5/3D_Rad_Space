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
	class E3DRSP_GRAPHICS_EXPORT LineList : public IPrimitive
	{
		std::unique_ptr<RasterizerState> _lineRasterizer;
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
		LineList(GraphicsDevice *device, std::span<VertexPositionColor> points);

		LineList(const LineList &) = delete;
		LineList(LineList &&) noexcept = default;

		LineList &operator=(const LineList &) = delete;
		LineList &operator=(LineList &&) noexcept = default;

		/// <summary>
		/// Gets the vertex buffer this instance was build with.
		/// </summary>
		/// <returns>Lines list</returns>
		VertexBufferV<VertexPositionColor>* GetVertexBuffer() const noexcept;
		/// <summary>
		/// Rasterizer state used to render lines.
		/// </summary>
		/// <returns>rasterizer state handle</returns>
		RasterizerState* GetLineRasterizer() const noexcept;

		/// <summary>
		/// Draws this primitive shape.
		/// </summary>
		virtual void Draw3D() override;
	};
}