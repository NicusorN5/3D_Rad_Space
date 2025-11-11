#pragma once
#include "IPrimitive.hpp"
#include "../../Core/FixedArray.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT Cylinder: public IPrimitive
	{
	public:
		Cylinder(IGraphicsDevice* device, float radius = 1.0f, float height = 1.0f, float tessellation = 64);

		[[nodiscard]] static FixedArray<VertexPositionColor> CreateCylinderVertices(
			float radius,
			float height,
			unsigned resolution, 
			Math::Color color
		);

		[[nodiscard]] static FixedArray<unsigned> CreateCylinderIndices(unsigned resolution);
	};
}