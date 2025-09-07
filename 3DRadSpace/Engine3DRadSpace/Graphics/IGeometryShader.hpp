#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IGeometryShader : public IShader
	{
	public:
		~IGeometryShader() override = default;
	};
}