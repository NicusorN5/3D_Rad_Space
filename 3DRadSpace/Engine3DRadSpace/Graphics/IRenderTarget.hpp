#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IRenderTarget
	{
	public:
		virtual void* RenderTargetHandle() const noexcept = 0;
		virtual ~IRenderTarget() = default;
	};
}