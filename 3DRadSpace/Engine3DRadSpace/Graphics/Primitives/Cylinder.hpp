#pragma once
#include "IPrimitive.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Represents a Cylinder shape formed by a triangle strip.
	/// </summary>
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT Cylinder: public IPrimitive
	{
	public:
		Cylinder(IGraphicsDevice* device, float radius = 1.0f, float height = 1.0f, float tessellation = 64, Math::Color color = Math::Colors::White);

		[[nodiscard]] static std::vector<VertexPositionColor> CreateCylinderVertices(
			float radius,
			float height,
			unsigned resolution, 
			Math::Color color
		);

		void Draw3D() override;
	};
}