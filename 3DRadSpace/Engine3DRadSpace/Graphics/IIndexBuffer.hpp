#pragma once
#include "IGPUBuffer.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IIndexBuffer : public IGPUBuffer
	{
	protected:
		IIndexBuffer() = default;
	public:
		virtual void Set(unsigned index) = 0;
		virtual unsigned NumIndices() const noexcept = 0;

		[[nodiscard]] virtual std::unique_ptr<IIndexBuffer> CreateStaging() = 0;

		~IIndexBuffer() override = default;
	};
}