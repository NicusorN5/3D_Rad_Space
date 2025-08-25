#pragma once
#include "FaceOperation.hpp"
#include "IGPUResource.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IDepthStencilState : public IGPUResource
	{
	protected:
		IDepthStencilState() = default;
	public:
		virtual unsigned int StencilRef() const noexcept = 0;
	};
}