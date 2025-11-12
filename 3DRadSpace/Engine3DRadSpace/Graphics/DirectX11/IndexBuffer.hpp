#pragma once
#include "IIndexBuffer.hpp"
#include "DirectX11.h"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class GraphicsDevice;
	/// <summary>
	/// Represents a index buffer.
	/// </summary>
	/// <remarks>
	/// Since this is a GPU resource, copy constructors are removed.
	/// </remarks>
	class E3DRSP_GRAPHICS_EXPORT IndexBuffer : IIndexBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> _indexBuffer;

		GraphicsDevice* _device;
		unsigned _numIndices;
		void _debugInfo();

		IndexBuffer(GraphicsDevice* device, Microsoft::WRL::ComPtr<ID3D11Buffer>&& buffer, unsigned numIndices);
	public:
		/// <summary>
		/// Constructs a index buffer from the specified indices.
		/// </summary>
		/// <param name="device">Graphics device handle.</param>
		/// <param name="indices">Array of indices. Must not be empty.</param>
		IndexBuffer(GraphicsDevice* device, std::span<unsigned> indices);

		IndexBuffer(IndexBuffer&) = delete;
		IndexBuffer(IndexBuffer&&) noexcept = default;

		IndexBuffer& operator=(IndexBuffer&) = delete;
		IndexBuffer& operator=(IndexBuffer&&) noexcept = default;

		/// <summary>
		/// Sets this index buffer to the GPU.
		/// </summary>
		/// <param name="index"></param>
		void Set(unsigned index = 0) override;
		/// <summary>
		/// Sets new indices to this index buffer instance.
		/// </summary>
		/// <param name="newindices"></param>
		void SetData(void* data, size_t buffSize);

		/// <summary>
		/// Maps this IndexBuffer to the CPU, so it can be read from. EndRead() must be called after!
		/// </summary>
		/// <param name="data">Pointer of a void* containing the indices.</param>
		/// <returns>The number of inidices</returns>
		size_t ReadData(void** data);
		/// <summary>
		/// Call after ReadDate(), so this IndexBuffer is unmapped from the CPU.
		/// </summary>
		void EndRead();

		/// <summary>
		/// Returns the number of indices this IndexBuffer instance has.
		/// </summary>
		/// <returns>Number of indices</returns>
		unsigned NumIndices() const noexcept override;
		/// <summary>
		/// Returns the native handle of this IndexBuffer.
		/// </summary>
		/// <returns>ID3D11Buffer on DirectX11.</returns>
		void* GetHandle() const noexcept override;

		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		[[nodiscard]] std::unique_ptr<IIndexBuffer> CreateStaging() override;

		~IndexBuffer() = default;

		friend class GraphicsDevice;
		friend class ModelMeshPart;
	};
}

