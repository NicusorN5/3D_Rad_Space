#pragma once
#include "IGPUResource.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IDepthStencilBuffer : public IGPUResource
	{
		IDepthStencilBuffer() = default;
	public:
		void* GetViewHandle() const noexcept override = 0;
		void* GetDepthTextureHandle() const noexcept override = 0;
		Texture2D* GetDepthTexture() const noexcept override = 0;

		void* GetHandle() const noexcept override = 0;

		Texture2D CloneDepthTexture() override = 0;
	};
}