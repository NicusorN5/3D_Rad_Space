#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IDomainShader : public IShader
	{
	public:
		~IDomainShader() override = default;
	};
}