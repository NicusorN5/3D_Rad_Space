#pragma once
#include "ITexture2D.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IRenderTarget : public ITexture2D
	{
	public:
		virtual void* RenderTargetHandle() const noexcept = 0;
		~IRenderTarget() override = default;
	};
}