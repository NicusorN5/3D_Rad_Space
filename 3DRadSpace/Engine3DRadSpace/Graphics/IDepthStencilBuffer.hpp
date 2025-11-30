#pragma once
#include "IGPUResource.hpp"

namespace Engine3DRadSpace::Graphics
{
	class ITexture2D;

	class IDepthStencilBuffer : public IGPUResource
	{
	public:
		virtual void* GetDepthTextureHandle() const noexcept = 0;
		virtual ITexture2D* GetDepthTexture() const noexcept = 0;

		virtual std::unique_ptr<ITexture2D> CloneDepthTexture() = 0;

		~IDepthStencilBuffer() override = default;
	};
}