#pragma once
#include "IGPUResource.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IGPUBuffer : public IGPUResource
	{
	protected:
		IGPUBuffer() = default;
	public:
		virtual size_t ReadData(void **data) = 0;
		virtual void SetData(void *data, size_t buffSize) = 0;
		virtual void EndRead() = 0;
	};
}