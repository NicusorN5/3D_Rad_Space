#pragma once
#include "IPrimitive.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class Cylinder: public IPrimitive
	{
	public:
		Cylinder(GraphicsDevice* device, float radius = 1.0f, float height = 1.0f, float tessellation = 64);
	};
}