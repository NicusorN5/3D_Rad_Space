#pragma once
#include "GraphicsDevice.hpp"
#include "VertexDeclarations.hpp"
#include "../Logging/Exception.hpp"
#include "IShader.hpp"
#include "BufferUsage.hpp"
#include "../IVertexBuffer.hpp"
#include "DirectX11.h"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class GraphicsDevice;

	class E3DRSP_GRAPHICS_DX11_EXPORT VertexBuffer : public IVertexBuffer
	{
		void _debugInfo();
	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;

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

		template<VertexDecl V>
		void SetData(std::span<V> newVerts)
		{
			SetData(newVerts[0], newVerts.size_bytes());
		}

		size_t ReadData(void** data);
		void EndRead();

		void Set();
		void Draw(unsigned startIndex = 0);

		size_t TotalSize() const noexcept;
		size_t StructSize() const noexcept;
		size_t NumVertices() const noexcept;

		void SetDebugName(const std::string& name);

		[[nodiscard]] std::unique_ptr<IVertexBuffer> CreateStaging() override;
		
		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		virtual ~VertexBuffer() = default;

		friend class GraphicsDevice;
		friend class GraphicsCommandList;
		friend class ModelMeshPart;
	};
}