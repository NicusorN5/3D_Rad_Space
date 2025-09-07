#pragma once
#include "GraphicsDevice.hpp"
#include "VertexDeclarations.hpp"
#include "../Core/Logging/Exception.hpp"
#include "IShader.hpp"
#include "BufferUsage.hpp"
#include "../IVertexBuffer.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class GraphicsDevice;

	class E3DRSP_GRAPHICS_EXPORT VertexBuffer : IVertexBuffer
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

		[[nodiscard]] VertexBuffer CreateStaging();

		~VertexBuffer() override = default;

		friend class GraphicsDevice;
		friend class ModelMeshPart;
	};

	template<VertexDecl V>
	class VertexBufferV : public VertexBuffer
	{
	public:
		VertexBufferV(_In_ GraphicsDevice* device, _In_ std::span<V> data, BufferUsage usage = BufferUsage::ReadOnlyGPU_WriteOnlyCPU);
		VertexBufferV(_In_ GraphicsDevice* device, std::nullptr_t no_data, size_t numVerts, BufferUsage usage = BufferUsage::ReadOnlyGPU_WriteOnlyCPU);

		void SetData(std::span<V> data);

		friend class GraphicsDevice;
	};

	template<VertexDecl V>
	VertexBufferV<V>::VertexBufferV(_In_ GraphicsDevice* device, _In_ std::span<V> data, BufferUsage usage) :
		VertexBuffer(device, &data[0], sizeof(V), data.size(), usage)
	{
	}

	template<VertexDecl V>
	VertexBufferV<V>::VertexBufferV(_In_ GraphicsDevice* device, std::nullptr_t no_data, size_t numVerts, BufferUsage usage) :
		VertexBuffer(device, nullptr, sizeof(V), numVerts, usage)
	{
		(void)no_data;
	}

	template<VertexDecl V>
	inline void VertexBufferV<V>::SetData(std::span<V> data)
	{
		(void)data;
	}
}