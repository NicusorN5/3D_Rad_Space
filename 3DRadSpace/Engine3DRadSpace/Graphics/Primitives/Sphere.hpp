#pragma once
#include "IPrimitive.hpp"
#include "../Shaders/BlankShader.hpp"
#include "../VertexBuffer.hpp"
#include "../IndexBuffer.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Represents a spherical shape.
	/// </summary>
	/// <remarks>
	/// Same remarks as the Box type.
	/// </remarks>
	class E3DRSP_GRAPHICS_EXPORT Sphere : public IPrimitive
	{
		float _radius;
	public:
		/// <summary>
		/// Constructs a sphere shape, with specified radius, color and shape resolution.
		/// </summary>
		/// <param name="device">Graphics device.</param>
		/// <param name="radius">Radius of the sphere.</param>
		/// <param name="color">Vertex color of the sphere.</param>
		/// <param name="resolution">Defines how accurate the sphere is.</param>
		Sphere(GraphicsDevice *device, float radius, Math::Color color, unsigned resolution);

		Sphere(const Sphere &) = delete;
		Sphere(Sphere &&) noexcept = default;

		Sphere &operator=(const Sphere &) = delete;
		Sphere &operator=(Sphere &&) noexcept = default;

		float GetRadius() const noexcept;

		void Draw3D() override;
	};
}