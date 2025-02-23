#pragma once
#include "IPrimitive.hpp"
#include "../../Algorithms/FixedArray.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class Cylinder: public IPrimitive
	{
	public:
		Cylinder(GraphicsDevice* device, float radius = 1.0f, float height = 1.0f, float tessellation = 64);

		[[nodiscard]] static Algorithms::FixedArray<VertexPositionColor> CreateCylinderVertices(float radius, float height, unsigned resolution, Color color);
		[[nodiscard]] static Algorithms::FixedArray<unsigned> CreateCylinderIndices(unsigned resolution);
	};
}