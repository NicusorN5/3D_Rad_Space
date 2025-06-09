#pragma once
#include "LineStrip.hpp"
#include "../../Core/Algorithms/FixedArray.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class E3DRSP_GRAPHICS_EXPORT Circle : public LineStrip
	{
		float _radius;
	public:
		Circle(GraphicsDevice* device, float radius = 1.0f, Math::Color color = Math::Colors::White, unsigned resolution = 100);

		[[nodiscard]] static Algorithms::FixedArray<VertexPositionColor> CreateCircleVertices(float radius, unsigned resolution, Math::Color color);

		float GetRadius() const noexcept;

		~Circle() = default;
	};
}