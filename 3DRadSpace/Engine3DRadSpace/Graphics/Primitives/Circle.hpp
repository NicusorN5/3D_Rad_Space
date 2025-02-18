/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/Primitives/Circle.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "Lines.hpp"
#include "../../Algorithms/FixedArray.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class DLLEXPORT Circle : public Lines
	{
		float _radius;
	public:
		Circle(GraphicsDevice* device, float radius = 1.0f, Color color = Colors::White, unsigned resolution = 100);

		static Algorithms::FixedArray<VertexPositionColor> CreateCircleVertices(float radius, unsigned resolution, Color color);

		void Draw3D() override;

		float GetRadius() const noexcept;

		~Circle() = default;
	};
}