#pragma once
#include "IGPUResource.hpp"
#include "../Math/UPoint.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents an cubemap made of 6 2D textures.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT ITextureCube : public IGPUResource
	{
	public:
		virtual Math::UPoint Size() const noexcept = 0;

		virtual unsigned Width() const noexcept = 0;
		virtual unsigned Height() const noexcept = 0;

		virtual void* GetViewHandle() const noexcept = 0;

		[[nodiscard]] virtual std::unique_ptr<ITextureCube> CreateStaging() = 0;

		virtual ~ITextureCube() override = default;
	};
}