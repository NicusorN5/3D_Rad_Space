#pragma once
#include "IPrimitive.hpp"

namespace Engine3DRadSpace::Math
{
	struct BoundingPlane;
}

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Represents a 3D plane.
	/// </summary>
	/// <remarks>
	/// Only the top side is drawn, because the rasterizer state will be not changed when drawing, unline "class Lines".
	/// Only a size parameter is used when creating the mesh, BoundingPlane represents a infinite plane.
	/// The mesh transformation is not set by a BoundingPlane since translation and scale information would need to be set again - it isn't guaranteed to recover translation and scale from a 
	/// </remarks>
	class E3DRSP_GRAPHICS_EXPORT Plane: public IPrimitive
	{
	public:
		/// <summary>
		/// Constructs a plane mesh, with specified size and color.
		/// </summary>
		/// <remarks>
		/// The constructed plane is centered at R^3(0,0,0), but it's area is still x*y.
		/// From the above fact, to construct a unit plane (size 1,1), Normal (0,1,0) it's okay to use size = Vector2::One().
		/// </remarks>
		/// <param name="device">GPU Device context.</param>
		/// <param name="color">Vertex color of the plane.</param>
		/// <param name="size">Size of the plane.</param>
		Plane(GraphicsDevice* device, const Math::Color& color, const Math::Vector2& size);

		/// <summary>
		/// Returns array of vertices assembling a XZ plane, centered at 0,0,0.
		/// </summary>
		/// <param name="color">Vertex color</param>
		/// <param name="size"></param>
		/// <returns></returns>
		static std::array<VertexPositionColor, 4> CreateVertices(const Math::Color &color, const Math::Vector2& size);
		/// <summary>
		/// Returns the indices of the plane mesh created by the CreateVertices() static method.
		/// </summary>
		/// <returns>6 indices representing 2 triangles.</returns>
		static std::array<unsigned, 6> CreateIndices();

		/// <summary>
		/// Draws the plane, with transformation specified as IPrimitive fields.
		/// </summary>
		void Draw3D() override;
	};
}