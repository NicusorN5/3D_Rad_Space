#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IFragmentShader : public IShader
	{
	public:
		~IFragmentShader() override = default;
	};
}