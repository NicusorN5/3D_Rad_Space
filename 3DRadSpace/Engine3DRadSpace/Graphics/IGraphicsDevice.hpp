#pragma once
#include "../Math/Point.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IGraphicsDevice
	{
	protected:
		IGraphicsDevice() = default;
	public:
		virtual ~IGraphicsDevice() = default;
	};
}