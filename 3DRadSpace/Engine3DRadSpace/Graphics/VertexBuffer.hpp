#pragma once
#include "GraphicsDevice.hpp"
#include "VertexDeclarations.hpp"
#include "../Core/Logging/Exception.hpp"
#include "IShader.hpp"
#include "BufferUsage.hpp"

namespace Engine3DRadSpace
{
	namespace Graphics
	{
		class GraphicsDevice;
		
		class E3DRSP_GRAPHICS_EXPORT VertexBuffer
		{
			void _debugInfo();
		protected:
#ifdef  USING_DX11
			Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;

			D3D11_USAGE _to_d3d11_usage(BufferUsage usage);
			UINT d3d11_cpu_usage(BufferUsage usage);
#endif //  USING_DX11
			GraphicsDevice* _device;

			size_t _numVerts;
			size_t _structSize;

			VertexBuffer(GraphicsDevice* device, Microsoft::WRL::ComPtr<ID3D11Buffer>&& vertexBuffer, size_t p_structSize, size_t numVertices);
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

			size_t TotalSize() const noexcept;
			size_t StructSize() const noexcept;
			size_t NumVertices() const noexcept;

			void SetDebugName(const std::string& name);

			[[nodiscard]] VertexBuffer CreateStaging();

			virtual ~VertexBuffer() = default;

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
#ifdef USING_DX11
			D3D11_MAPPED_SUBRESOURCE resource{};
			HRESULT r = _device->_context->Map(_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
			if (FAILED(r)) throw Logging::Exception("Failed to map a vertex buffer that cannot be written by the CPU.");
			
			memset(resource.pData, 0, _numVerts * _structSize);
			memcpy_s(resource.pData, data.size_bytes(), &data[0], data.size_bytes());

			_device->_context->Unmap(_buffer.Get(), 0);
#endif
		}
	}
}