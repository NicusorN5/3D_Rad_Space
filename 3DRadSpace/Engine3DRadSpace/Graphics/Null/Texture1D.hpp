#pragma once
#include "../ITexture1D.hpp"
#include "GraphicsDevice.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class Texture1D : public ITexture1D
	{
	public:
		Texture1D(GraphicsDevice* device, size_t numElements, PixelFormat format);
		Texture1D(GraphicsDevice* device, std::span<Math::Color> colors);

		Texture1D(const Texture1D&) = delete;
		Texture1D(Texture1D&&) noexcept = default;

		Texture1D& operator=(const Texture1D&) = delete;
		Texture1D& operator=(Texture1D&&) noexcept = default;

		size_t Length() const noexcept override;
		void* GetViewHandle() const noexcept override;
		[[nodiscard]] std::unique_ptr<ITexture1D> CreateStaging() override;

		size_t ReadData(void** data) override;
		void SetData(void* data, size_t buffSize) override;
		void EndRead() override;

		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		~Texture1D() override = default;
	};
}