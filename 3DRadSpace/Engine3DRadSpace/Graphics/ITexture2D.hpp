#pragma once
#include "IGPUBuffer.hpp"
#include "../Math/Point.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT ITexture2D : public IGPUBuffer
	{
	public:
		virtual Math::Point Size() const noexcept = 0;

		virtual unsigned Width() const noexcept = 0;
		virtual unsigned Height() const noexcept = 0;

		virtual void* GetViewHandle() const noexcept = 0;

		[[nodiscard]] virtual std::unique_ptr<ITexture2D> CreateStaging() = 0;
	
		virtual void SaveToFile(const std::filesystem::path& path) = 0;

		virtual ~ITexture2D() override = default;
	};
}