#pragma once
#include "../IIndexBuffer.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class GraphicsDevice;

	class E3DRSP_GRAPHICS_NULL_EXPORT IndexBuffer final : public IIndexBuffer
	{
	public:
		IndexBuffer(GraphicsDevice* device, std::span<unsigned> indices);
		IndexBuffer(GraphicsDevice* device, unsigned* indices, size_t numindices);

		IndexBuffer(IndexBuffer &) = delete;
		IndexBuffer(IndexBuffer &&) noexcept = default;

		IndexBuffer &operator=(IndexBuffer &) = delete;
		IndexBuffer &operator=(IndexBuffer &&) noexcept = default;

		void Set(unsigned index = 0) override;
		void SetData(void* buffer, size_t bufferSize) override;

		size_t ReadData(void** data) override;
		void EndRead() override;

		unsigned NumIndices() const noexcept override;

		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		[[nodiscard]] std::unique_ptr<IIndexBuffer> CreateStaging() override;
	};
}

