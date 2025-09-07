#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IVertexShader : public IShader
	{
	public:
		~IVertexShader() override = default;
	};
}