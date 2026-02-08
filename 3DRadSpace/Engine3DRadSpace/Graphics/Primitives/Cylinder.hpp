#pragma once
#include "IPrimitive.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT Cylinder: public IPrimitive
	{
	public:
		Cylinder(IGraphicsDevice* device, float radius = 1.0f, float height = 1.0f, float tessellation = 64);

		[[nodiscard]] static std::vector<VertexPositionColor> CreateCylinderVertices(
			float radius,
			float height,
			unsigned resolution, 
			Math::Color color
		);

		[[nodiscard]] static std::vector<unsigned> CreateCylinderIndices(unsigned resolution);
	};
}