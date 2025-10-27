#pragma once
#include "IIndexBuffer.hpp"

namespace Engine3DRadSpace
{
	namespace Graphics
	{
		class GraphicsDevice;
		/// <summary>
		/// Represents a index buffer.
		/// </summary>
		/// <remarks>
		/// Since this is a GPU resource, copy constructors are removed.
		/// Creating IndexBuffers with 0 length will result in errors - debug layer errors or segmentation faults from the GPU driver, possibly terminating the application.
		/// </remarks>
		class E3DRSP_GRAPHICS_EXPORT IndexBuffer : IIndexBuffer
		{
#ifdef USING_DX11
			Microsoft::WRL::ComPtr<ID3D11Buffer> _indexBuffer;
#endif
			GraphicsDevice* _device;

			unsigned _numIndices;

			void _debugInfo();

#ifdef USING_DX11
			IndexBuffer(GraphicsDevice* device, Microsoft::WRL::ComPtr<ID3D11Buffer>&& buffer,unsigned numIndices);
#endif
		public:
			/// <summary>
			/// Constructs a index buffer from the specified indices.
			/// </summary>
			/// <param name="device">Graphics device handle.</param>
			/// <param name="indices">Array of indices. Must not be empty.</param>
			IndexBuffer(GraphicsDevice* device, std::span<unsigned> indices);
			/// <summary>
			/// Constructs a index buffer from the specified indices.
			/// </summary>
			/// <param name="device">Graphics device.</param>
			/// <param name="indices">Pointer to a array of unsigned indices.</param>
			/// <param name="numindices">Number of indices. Must not be 0.</param>
			IndexBuffer(GraphicsDevice* device, unsigned* indices, size_t numindices);

			IndexBuffer(IndexBuffer &) = delete;
			IndexBuffer(IndexBuffer &&) noexcept = default;

			IndexBuffer &operator=(IndexBuffer &) = delete;
			IndexBuffer &operator=(IndexBuffer &&) noexcept = default;

			/// <summary>
			/// Sets this index buffer to the GPU.
			/// </summary>
			/// <param name="index"></param>
			void Set(unsigned index = 0);
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
			unsigned NumIndices() const noexcept;
			/// <summary>
			/// Returns the native handle of this IndexBuffer.
			/// </summary>
			/// <returns>ID3D11Buffer on DirectX11.</returns>
			void* GetHandle() const noexcept;

			IndexBuffer CreateStaging();

			~IndexBuffer() = default;

			friend class GraphicsDevice;
			friend class ModelMeshPart;
		};
	}
}

