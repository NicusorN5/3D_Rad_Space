#pragma once

#include "../../Math/BoundingBox.hpp"
#include "IPrimitive.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Represents a plain vertex coloured 3D box, without normals and UVs.
	/// </summary>
	/// <remarks>
	/// You will only want one instance of this per application, since a Box instance owns a single pair of vertex and index buffers.
	/// Draw multiple boxes using multiple Draw3D calls. Between each call, change the transform.
	/// To draw multiple coloured boxes in one frame, avoid SetColor() calls, and use a shader that doesn't use vertex colouring.
	/// Since making clones of this type is not recommended, copy constructors are removed.
	/// Move constructors are preserved to allow use in containers.
	/// Do not use negative scales - unless back face culling is disabled.
	/// Avoid using GetVertexBuffer() and GetIndexBuffer(). Prefer the CreateVertices and CreateIndices static methods.
	/// </remarks>
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT Box : public IPrimitive
	{
		Math::BoundingBox _box;
		Math::Color _color;

	public:
		/// <summary>
		/// Constructs a box mesh from given bounding box and single color.
		/// </summary>
		/// <param name="device">Graphics device used to create vertex and index buffers.</param>
		/// <param name="b">Bounding box representing the boundaries of the mesh.</param>
		/// <param name="color">Color of the mesh.</param>
		Box(GraphicsDevice *device, const Math::BoundingBox &b, Math::Color color);

		/// <summary>
		/// Creates the vertices of the box given by b.
		/// </summary>
		/// <param name="b">Bounding box.</param>
		/// <param name="color">Color.</param>
		/// <returns>8 position-color vertices.</returns>
		static std::array<VertexPositionColor, 8> CreateVertices(const Math::BoundingBox &b, const Math::Color &color);
		/// <summary>
		/// Creates the indices of the box mesh.
		/// </summary>
		/// <returns>a 36 number long array representing the order of the box vertices.</returns>
		static std::array<unsigned, 36> CreateIndices();

		Box(const Box &) = delete;
		Box(Box &&b) noexcept = default;

		Box &operator=(const Box &) = delete;
		Box &operator=(Box &&b) noexcept = default;

		/// <summary>
		/// Gets the boundaries of the mesh.
		/// </summary>
		/// <returns>Box position and scale.</returns>
		Math::BoundingBox GetBoundingBox() const noexcept;
		void SetBoundingBox(const Math::BoundingBox &b);

		/// <summary>
		/// Gets the color this instance was created with.
		/// </summary>
		/// <returns>Color</returns>
		Math::Color GetColor() const noexcept;
		/// <summary>
		/// Sets an other color to this instance.
		/// </summary>
		/// <param name="color">New color</param>
		void SetColor(const Math::Color& color);

		/// <summary>
		/// Gets the internal vertex buffer.
		/// </summary>
		/// <returns>Box vertex buffer</returns>
		VertexBufferV<VertexPositionColor>* GetVertexBuffer() const noexcept;
		/// <summary>
		/// Gets the internal index buffer.
		/// </summary>
		/// <returns>Index buffer.</returns>
		IndexBuffer* GetIndexBuffer() const noexcept;

		/// <summary>
		/// Draws the box once, with specified transform.
		/// </summary>
		virtual void Draw3D() override;
	};
}