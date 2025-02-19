#pragma once
#include "LineStrip.hpp"
#include "../../Algorithms/FixedArray.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class DLLEXPORT Circle : public LineStrip
	{
		float _radius;
	public:
		Circle(GraphicsDevice* device, float radius = 1.0f, Color color = Colors::White, unsigned resolution = 100);

		static Algorithms::FixedArray<VertexPositionColor> CreateCircleVertices(float radius, unsigned resolution, Color color);

		float GetRadius() const noexcept;

		~Circle() = default;
	};
}