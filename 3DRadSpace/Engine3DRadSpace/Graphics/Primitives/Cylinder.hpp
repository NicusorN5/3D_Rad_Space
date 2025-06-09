#pragma once
#include "IPrimitive.hpp"
#include "../../Core/Algorithms/FixedArray.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class E3DRSP_GRAPHICS_EXPORT Cylinder: public IPrimitive
	{
	public:
		Cylinder(GraphicsDevice* device, float radius = 1.0f, float height = 1.0f, float tessellation = 64);

		[[nodiscard]] static Algorithms::FixedArray<VertexPositionColor> CreateCylinderVertices(
			float radius,
			float height,
			unsigned resolution, 
			Math::Color color
		);
		[[nodiscard]] static Algorithms::FixedArray<unsigned> CreateCylinderIndices(unsigned resolution);
	};
}