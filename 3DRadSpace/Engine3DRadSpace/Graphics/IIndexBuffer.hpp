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
		virtual void SetData(std::span<unsigned> newindices) = 0;
	};
}