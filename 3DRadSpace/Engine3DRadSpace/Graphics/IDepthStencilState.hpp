#pragma once
#include "FaceOperation.hpp"
#include "IGPUResource.hpp"
#include "DepthWriteMask.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IDepthStencilState : public IGPUResource
	{
	protected:
		IDepthStencilState() = default;
	public:
		virtual unsigned int StencilRef() const noexcept = 0;

		~IDepthStencilState() override = default;
	};
}