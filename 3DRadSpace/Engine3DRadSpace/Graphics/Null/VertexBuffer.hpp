#pragma once
#include "GraphicsDevice.hpp"
#include "VertexDeclarations.hpp"
#include "../Logging/Exception.hpp"
#include "IShader.hpp"
#include "BufferUsage.hpp"
#include "../IVertexBuffer.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class GraphicsDevice;

	class E3DRSP_GRAPHICS_NULL_EXPORT VertexBuffer : public IVertexBuffer
	{
	public:
		VertexBuffer(
			_In_ GraphicsDevice* device,
			_In_reads_bytes_opt_(p_structSize * numVertices) const void* data,
			size_t p_structSize,
			size_t numVertices,
			BufferUsage usage = BufferUsage::ReadOnlyGPU
		);

		VertexBuffer(VertexBuffer &) = delete;
		VertexBuffer(VertexBuffer &&) noexcept = default;

		VertexBuffer &operator=(VertexBuffer &) = delete;
		VertexBuffer &operator=(VertexBuffer &&) noexcept = default;

		void SetData(void* data, size_t dataSize);

		size_t ReadData(void** data);
		void EndRead();

		void Set();
		void Draw(unsigned startIndex = 0);

		size_t TotalSize() const noexcept override;
		size_t StructSize() const noexcept override;
		size_t NumVertices() const noexcept override;

		void SetDebugName(const std::string& name);

		[[nodiscard]] std::unique_ptr<IVertexBuffer> CreateStaging() override;

		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		~VertexBuffer() override = default;

		friend class GraphicsDevice;
		friend class ModelMeshPart;
	};
}