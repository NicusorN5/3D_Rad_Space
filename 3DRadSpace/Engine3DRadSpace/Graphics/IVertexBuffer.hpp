#pragma once
#include "GPUBuffer.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IVertexBuffer : public GPUBuffer
	{
	public:
		size_t TotalSize() const noexcept = 0;
		size_t StructSize() const noexcept = 0;
		size_t NumVertices() const noexcept = 0;

		[[nodiscard]] std::unique_ptr<IVertexBuffer> CreateStaging() = 0;
	};
}